
#include "codeGen/ast/GenerateFileVisitor.h"
#include "logger/LoggerManager.h"

#include "codeGen/ast/LlvmFunctionNode.h"
#include "codeGen/ast/LlvmBasicBlockNode.h"
#include "codeGen/ast/LlvmInstructionNode.h"
#include "codeGen/BracketManager.h"
#include "codeGen/DefineVariablesHandler.h"
#include "settings/CodegenSettings.h"
#include "utils/CodeGenUtils.h"
#include "codeGen/GenerateFnHeader.h"
#include "codeGen/TranslateOperator.h"

#include <llvm/ADT/PostOrderIterator.h>
#include <llvm/Analysis/PostDominators.h>
#include "llvm/Support/Casting.h"

#include <filesystem>
#include <fstream>
#include <functional>


std::pair<std::string, std::string> codeGen::ast::GenerateFileVisitor::visit(std::shared_ptr<LlvmFunctionNode> node) {
    // Iterate over all basic blocks and instructions and generate the LLVM IR code.
    for(auto &child: node->getChildren()) {
        auto [name, code] = visit(std::dynamic_pointer_cast<LlvmBasicBlockNode>(child));
        logger->info("Basic block name: {}", name);
    }

    // !!!!! Replace stack variables with their aliases at the end of everything.
    replaceStackVarWithAlias(PHINodeHandler{llvmFun}.getPHINodeAliases());
    replaceVarsThatNeedToBeReplacedAtEnd();
    sanitizeReturnValuesForVoidTypeFunctions();
    return std::make_pair<std::string, std::string>(node->getName(), "");
}

std::pair<std::string, std::string>
codeGen::ast::GenerateFileVisitor::visit(std::shared_ptr<LlvmInstructionNode> node) {
    auto nodeName = node->getName();
    auto instr = utils::CodeGenUtils::getInstructionAfterLabel(llvmFun, nodeName, node->getOpcode() == llvm::Instruction::Ret);
    if(!instr)
    {
        logger->error("[GenerateFileVisitor::visit(InstructionNode)] Failed to get LLVM instruction after label: {}", nodeName);
        return std::make_pair<std::string, std::string>(node->getName(), "");
    }
    logger->info("[GenerateFileVisitor::visit(InstructionNode)] Instruction name: {}, body: {}", instr->hasName() ? nodeName : instr->getOpcodeName(), node->getInstructionBody());

    // ignore phi nodes instructions, they are handled separately.
    if(instr->getOpcode() == llvm::Instruction::PHI)
    {
        logger->info("[GenerateFileVisitor::visit(InstructionNode)] Skipping PHI node instruction: {}", nodeName);
        return std::make_pair<std::string, std::string>(node->getName(), "");
    }

    if(instr->getOpcode() == llvm::Instruction::Ret && node->getOpcode() == llvm::Instruction::Ret && utils::CodeGenUtils::isBasicBlockTerminal(llvmFun, lastBasicBlockName))
    {
        auto returnBody = getFinalReturnBody(lastBasicBlockName);
        logger->info("[GenerateFileVisitor::visit(InstructionNode)] Found return value from last basic block: {}, with value: {}", nodeName, returnBody);
        output[lastBasicBlockName].push_back(utils::CodeGenUtils::getSpaces(indentationLevel) + returnBody);
        return std::make_pair<std::string, std::string>(node->getName(), "");
    }

    if(instr->isCast())
    {
        logger->info("[GenerateFileVisitor::visit(InstructionNode)] Skipping cast instruction: {}, with body: {}", nodeName, node->getInstructionBody());
        node->setInstructionBody(utils::CodeGenUtils::extractRHSFromInstructionBody(node->getInstructionBody()));
        variablesToBeReplacedAtTheEnd.emplace(nodeName, node->getInstructionBody());
        return std::make_pair<std::string, std::string>(node->getName(), "");
    }

    // Only print terminator instructions if they have multiple uses.
    // Why? Because they are usually conditions for loops/ifs and there is no need
    // to print them twice if they are not used anywhere else.
    auto terminatorName = utils::CodeGenUtils::getTerminatorAlias(llvmFun, instr);
    logger->info("[GenerateFileVisitor::visit(InstructionNode)] Terminator name: {} and node name: {}", terminatorName, nodeName);
    if(nodeName == terminatorName && utils::CodeGenUtils::doesInstructionHaveSingleUse(instr))
    {
        logger->info("[GenerateFileVisitor::visit(InstructionNode)] Skipping printing for the node: {}", nodeName);
        return std::make_pair<std::string, std::string>(node->getName(), "");
    }

    if(utils::CodeGenUtils::isInstructionUsedInTernaryOperatorAndHasSingleUse(instr))
    {
        logger->info("[GenerateFileVisitor::visit(InstructionNode)] Skipping printing for the node(condition for select instruction): {}", nodeName);
        singleUseVariables.emplace(nodeName, node->getInstructionBody());
        return std::make_pair<std::string, std::string>(node->getName(), "");
    }

    if(instr->getOpcode() == llvm::Instruction::Select)
    {
        // get condition for select and check if it is used in a ternary operator.
        if(auto* selectInst = llvm::dyn_cast<llvm::SelectInst>(instr))
        {
            auto condition = selectInst->getCondition();
            auto search = std::find_if(singleUseVariables.begin(), singleUseVariables.end(), [&](auto &pair) {
                return pair.first == condition->getName().str();
            });

            if(search != singleUseVariables.end())
            {
                // search for the single use variable in the instruction body and replace it with its value.
                auto singleUseVar = search->first;
                auto singleUseVarValue = search->second;
                auto selectInstBody = node->getInstructionBody();
                if(selectInstBody.find(singleUseVar + " ") != std::string::npos)
                {
                    auto toReplace = utils::CodeGenUtils::extractLHSFromInstructionBody(singleUseVarValue);
                    selectInstBody.replace(selectInstBody.find(singleUseVar), singleUseVar.length(), toReplace);
                    node->setInstructionBody(selectInstBody);
                }
            }
        }
    }

    auto indentation = utils::CodeGenUtils::getSpaces(indentationLevel);
    output[lastBasicBlockName].push_back(indentation +  node->getInstructionBody());

    return std::make_pair<std::string, std::string>(node->getName(), "");
}

bool codeGen::ast::GenerateFileVisitor::checkAndReplaceSingleUseVars(std::shared_ptr<LlvmInstructionNode> &node) {
    auto doesInstrBodyContainSingleUseVar = std::find_if(singleUseVariables.begin(), singleUseVariables.end(), [&](auto &pair) {
        return node->getInstructionBody().find(pair.first + " ") != std::string::npos;
    });

    if(doesInstrBodyContainSingleUseVar != singleUseVariables.end())
    {
        // search for the single use variable in the instruction body and replace it with its value.
        auto singleUseVar = doesInstrBodyContainSingleUseVar->first;
        auto singleUseVarValue = doesInstrBodyContainSingleUseVar->second;
        auto instrBody = node->getInstructionBody();
        auto pos = instrBody.find(singleUseVar + " ");
        instrBody.replace(pos, singleUseVar.length() + 1, singleUseVarValue);

        node->setInstructionBody(instrBody);
        // delete the single use variable from the map.
        singleUseVariables.erase(doesInstrBodyContainSingleUseVar);
        return true;
    }
    return false;
}

std::pair<std::string, std::string> codeGen::ast::GenerateFileVisitor::visit(std::shared_ptr<LlvmBasicBlockNode> node) {
    output.emplace(node->getName(), std::vector<std::string>());
    logger->info("[GenerateFileVisitor::visit(BasicBlock)] Basic block being processed: <{}>", node->getName());
    lastBasicBlockName = node->getName();
    auto bbInfo = funcInfo.getBBInfo(lastBasicBlockName);

    if(!areVariablesDefined)
    {
        areVariablesDefined = true;
        addVariablesDefinitions();
    }

    auto closeConditional = codeGen::BracketManager::shouldCloseConditional(node->getName(), funcInfo);
    logger->info("[GenerateFileVisitor::visit(BasicBlock)] Close conditional: {}", udm::BBInfo::getConditionalTypeString(
            static_cast<size_t>(closeConditional)));
    while(closeConditional != udm::BBInfo::ConditionalType::NONE)
    {
        indentationLevel -= 4;
        auto space = utils::CodeGenUtils::getSpaces(indentationLevel);

        output[lastBasicBlockName].push_back(space + "}");


        logger->info("[GenerateFileVisitor::visit(BasicBlock)] Closing conditional for basic block: {}", node->getName());
        closeConditional = codeGen::BracketManager::shouldCloseConditional(node->getName(), funcInfo);
    }

    auto val = codeGen::BracketManager::shouldCloseElse(node->getName(), funcInfo, llvmFun);
    if(val)
    {
        output[lastBasicBlockName].emplace_back("} else {");
    }
//    if(codeGen::BracketManager::shouldCloseElse(node->getName(), funcInfo, llvmFun))
//    {
//        indentationLevel -= 4;
//        auto space = utils::CodeGenUtils::getSpaces(indentationLevel);
//        output[lastBasicBlockName].push_back(space + "} else {");
//        logger->info("[GenerateFileVisitor::visit(BasicBlock)] Closing else for basic block: {}", node->getName());
//    }

    while(codeGen::BracketManager::shouldCloseReturn(node->getName(), funcInfo))
    {
        indentationLevel -= 4;
        auto space = utils::CodeGenUtils::getSpaces(indentationLevel);
        output[lastBasicBlockName].push_back(space + "}");
        logger->info("[GenerateFileVisitor::visit(BasicBlock)] Closing return for basic block: {}", node->getName());
    }

    for(auto &child: node->getChildren()) {
        auto [name, code] = visit(std::dynamic_pointer_cast<LlvmInstructionNode>(child));
    }

    if(codeGen::BracketManager::isLoop(bbInfo) == udm::BBInfo::LoopType::WHILE
        || codeGen::BracketManager::isLoop(bbInfo) == udm::BBInfo::LoopType::DO_WHILE
    )
    {
        codeGen::BracketManager::addBracket(node->getName(), funcInfo, llvmFun);
        auto space = utils::CodeGenUtils::getSpaces(indentationLevel);

        auto condition = utils::CodeGenUtils::getTerminatorCondition(llvmFun, node->getName());
        auto conditionBody = utils::CodeGenUtils::getBranchInstrBodyGivenBlock(llvmFun, condition.first);
        conditionBody = utils::CodeGenUtils::extractLHSFromInstructionBody(conditionBody);

        auto bb = utils::CodeGenUtils::getBBAfterLabel(llvmFun, node->getName());
        std::string nextBBName;
        if(bb)
        {
            // get the name of the next basic block.
            auto nextBB = bb->getNextNode();
            if(nextBB)
            {
                nextBBName = nextBB->getName();
            }
        }
        const bool isLoopConditionReversed = nextBBName.empty() ? utils::CodeGenUtils::isLoopConditionReversed(node->getName(), llvmFun) : utils::CodeGenUtils::isLoopConditionReversed(nextBBName, llvmFun);
        logger->info("[GenerateFileVisitor::visit(BasicBlock)] Is Loop condition reversed: {} for basic block: {}, respectively original: {}", isLoopConditionReversed, nextBBName, node->getName());
        conditionBody = !conditionBody.empty() && isLoopConditionReversed ? codeGen::TranslateOperator::negateAllOperatorsInExpression(conditionBody) : conditionBody;
        auto condStr = conditionBody.empty()  ? "true" : conditionBody;

        if(codeGen::BracketManager::isLoop(bbInfo) == udm::BBInfo::LoopType::DO_WHILE)
        {
            output[lastBasicBlockName].push_back(space + "do {");
        }
        else
        {
            output[lastBasicBlockName].push_back(space + "while (" + condStr + ") {");
        }
        indentationLevel += 4;
    }

    if(codeGen::BracketManager::isConditional(bbInfo))
    {
        codeGen::BracketManager::addBracket(node->getName(), funcInfo, llvmFun);
        auto space = utils::CodeGenUtils::getSpaces(indentationLevel);

        auto branchToTerminalBlockResult = utils::CodeGenUtils::checkIfCurrentBlockBranchesToTerminalBlock(llvmFun, node->getName());
        logger->info("[GenerateFileVisitor::visit(BasicBlock)] Branching to terminal block result: <{}, {}>", branchToTerminalBlockResult.isBranchingToTerminalBlock, branchToTerminalBlockResult.isConditionReversed);
        if (branchToTerminalBlockResult.isBranchingToTerminalBlock)
        {
            codeGen::BracketManager::handleBracketsWhenAddingReturn(node->getName(), funcInfo, llvmFun);
        }

        auto condition = utils::CodeGenUtils::getTerminatorCondition(llvmFun, node->getName());
        auto conditionBody = utils::CodeGenUtils::getBranchInstrBodyGivenBlock(llvmFun, condition.first);
        conditionBody = utils::CodeGenUtils::extractLHSFromInstructionBody(conditionBody);
        // really ugly hack to handle the case when the condition is reversed.
        conditionBody = !conditionBody.empty() && branchToTerminalBlockResult.isConditionReversed ? codeGen::TranslateOperator::negateAllOperatorsInExpression(conditionBody) : conditionBody;

        auto condStr = conditionBody.empty()  ? "true" : conditionBody;

        output[lastBasicBlockName].push_back(space + "if (" + condStr + ") {");
        indentationLevel += 4;
        if(branchToTerminalBlockResult.isBranchingToTerminalBlock)
        {
            logger->info("[GenerateFileVisitor::visit(BasicBlock)] Adding return value for conditional block: {}", node->getName());
            addReturnValue(node->getName());
        }
    }

    auto closing = codeGen::BracketManager::shouldCloseLoop(node->getName(), funcInfo);
    logger->info("[GenerateFileVisitor::visit(BasicBlock)] Closing loop for basic block: {}, type: {}", node->getName(), closing == udm::BBInfo::LoopType::NONE ? "NONE" : "DO_WHILE");
    while( closing != udm::BBInfo::LoopType::NONE)
    {
        std::cout << "WTF LOOP\n";
        indentationLevel -= 4;
        auto space = utils::CodeGenUtils::getSpaces(indentationLevel);
        if(closing == udm::BBInfo::LoopType::DO_WHILE)
        {
            output[lastBasicBlockName].push_back(space + "} while (" + utils::CodeGenUtils::getTerminatorCondition(llvmFun, node->getName()).second + ");");
        }
        else
        {
            output[lastBasicBlockName].push_back(space + "}");
        }
        closing = codeGen::BracketManager::shouldCloseLoop(node->getName(), funcInfo);
    }

    return std::make_pair<std::string, std::string>(node->getName(), "");
}

void codeGen::ast::GenerateFileVisitor::addVariablesDefinitions() {

    std::unordered_map<std::string, std::vector<codeGen::Variable>> orderedByTypeVariables;
    for(auto [key, vec]: definedVariables)
    {
        for(auto &var: vec)
        {
            orderedByTypeVariables[var.getType()].push_back(var);
        }
    }

    for(auto& [key, vec] : orderedByTypeVariables)
    {
        auto indentation = utils::CodeGenUtils::getSpaces(indentationLevel);
        std::string lastType, firstValName, varStr;
        std::size_t countVars = 0;

        if(!vec.empty())
        {
            lastType = vec.front().getType();
            firstValName = vec.front().getName();
        }

        for(auto &var: vec)
        {
            logger->info("[GenerateFileVisitor::addVariablesDefinitions] Variable name: {}, type: {}, initial value: {}", var.getName(), var.getType(), varStr);
            // If the type of the variable is different from the last one, then we need to add a new line.
            if(var.getType() != lastType)
            {
                output[lastBasicBlockName].push_back(varStr);
                varStr = "";
                lastType = var.getType();
                countVars = 0;
            }

            // If the variable is the first one, then we need to add the type.
            if(countVars == 0)
            {
                varStr += indentation + var.getType() + " " + var.getName() + " = " + var.getInitialValue();
                countVars++;
                lastType = var.getType();
                continue;
            }

            // If the variable is not the first one, then we need to add a comma.
            varStr += ", " + var.getName() + " = " + var.getInitialValue();
            countVars++;
            lastType = var.getType();


            //  If we have 2 variables in the same line, then we need to add a new line.
            if(countVars > 4 || varStr.size() > 45)
            {
                output[lastBasicBlockName].push_back(varStr);
                varStr = "";
                lastType = var.getType();
                countVars = 0;
            }
        }

        // if we have a build up string that was not added, now it is the time to do it.
        if(!varStr.empty())
        {
            output[lastBasicBlockName].push_back(varStr);
        }
    }
}

codeGen::ast::GenerateFileVisitor::GenerateFileVisitor(llvm::Function& fun)
: indentationLevel(0),
llvmFun(fun),
defVarHandler(fun),
areVariablesDefined(false)
{
    definedVariables = defVarHandler.handle();
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}

void codeGen::ast::GenerateFileVisitor::setFuncInfo(const udm::FuncInfo &funcInfo) {
    this->funcInfo = funcInfo;
}

udm::FuncInfo codeGen::ast::GenerateFileVisitor::getFuncInfo() const {
    return funcInfo;
}

std::unordered_map<std::string, std::vector<std::string>> codeGen::ast::GenerateFileVisitor::getOutput() const {
    return output;
}

void codeGen::ast::GenerateFileVisitor::addPhiNodesValues(const std::pair<std::string, std::string> &phiNode) {
    const auto& [bbStr, value] = phiNode;
    if (output.find(bbStr) == output.end())
    {
        return;
    }
    std::string space = utils::CodeGenUtils::getSpaces(0);
    if (!output[bbStr].empty())
    {
        auto copyFirstStrFromOutput = output[bbStr].front();
        logger->info("[GenerateFileVisistor::addPhiNodesValues] Label: {}", bbStr);
        logger->info("[GenerateFileVisistor::addPhiNodesValues] Copy first str from output: {}", copyFirstStrFromOutput);
        std::size_t pos = copyFirstStrFromOutput.find_first_not_of(" \t");
        if (pos != std::string::npos)
        {
            space = utils::CodeGenUtils::getSpaces(pos);
        }
    }
    logger->info("[GenerateFileVisistor::addPhiNodesValues] Adding phi node spaces: {}", space.size());
    output[bbStr].push_back(space + value);
}

void codeGen::ast::GenerateFileVisitor::replaceStackVarWithAlias(const std::vector<codeGen::ast::StackVarAlias> &aliases)
{
    for(const auto& alias: aliases)
    {
        logger->info("[GenerateFileVisitor::replaceStackVarWithAlias] Looking for stack var: {} in basic block: {}", alias.getStackVarName(), alias.getBasicBlockName());
        replaceOneStackVarWithAlias(alias);
    }
}

void codeGen::ast::GenerateFileVisitor::replaceOneStackVarWithAlias(const codeGen::ast::StackVarAlias &alias)
{
    for(const auto& [bbKey, vec]: output)
    {
        for(std::size_t i = 0;  i < vec.size(); ++i)
        {
            if(bbKey == alias.getBasicBlockName() || alias.getBasicBlockName() == "global")
            {
                std::string line = vec[i];
                std::size_t pos = line.find(alias.getStackVarName());
                if(pos != std::string::npos)
                {
                    std::string oldVal = line.substr(pos, alias.getStackVarName().size());
                    logger->info("[GenerateFileVisitor::replaceOneStackVarWithAlias] Found stack var: {} in line: {}, replacing old value: {} with: {}", alias.getStackVarName(), line, oldVal, alias.getLocalVar());
                    line.replace(pos, alias.getStackVarName().size(), alias.getLocalVar());
                    output[bbKey][i] = line;
                }
            }
        }
    }
}

void codeGen::ast::GenerateFileVisitor::addReturnValue(const std::string &bbLabel) {
    auto space = utils::CodeGenUtils::getSpaces(indentationLevel);
    output[bbLabel].push_back(space + utils::CodeGenUtils::returnStringForBranchingToTerminalBlock(llvmFun, bbLabel));
}

bool codeGen::ast::GenerateFileVisitor::writeToFile(const std::string &filename) {
    const std::string& outputPath = settings::CodegenSettings::getInstance()->getOutputFilePath();
    if (!std::filesystem::exists(outputPath))
    {
        if (!std::filesystem::create_directory(outputPath))
        {
            logger->error("[GenerateFileVisitor::writeToFile] Could not create directory: {}", outputPath);
            return false;
        }
    }

    const std::string& outputFilePath = outputPath + "/" + filename;
    std::ofstream outputFile(outputFilePath);

    if(!outputFile.is_open())
    {
        logger->error("[GenerateFileVisitor::writeToFile] Could not open file: {}", outputFilePath);
        return false;
    }

    codeGen::GenerateFnHeader fnHeaderGenerator(llvmFun);
    outputFile << fnHeaderGenerator.generate();

    for(auto &bb: llvmFun)
    {
        auto key = bb.getName().str();
        if (output.find(key) == output.end())
        {
            logger->error("[GenerateFileVisitor::writeToFile] Basic block not found: <{}> while printing to file", key);
            continue;
        }

        for(const auto& el: output[key])
        {
            outputFile << + "\t" + el + "\n";
        }
    }
    outputFile << "}\n";
    outputFile.close();
    return true;
}

std::string codeGen::ast::GenerateFileVisitor::getFinalReturnBody(const std::string &bbLabel) {
    std::string returnBody = "return ";
    auto basicBlock = utils::CodeGenUtils::getBBAfterLabel(llvmFun, bbLabel);
    if(basicBlock == nullptr)
    {
        logger->error("[GenerateFileVisitor::getFinalReturnBody] Could not find basic block after label: {}", bbLabel);
        return returnBody;
    }

    auto terminator = basicBlock->getTerminator();
    if(terminator == nullptr)
    {
        logger->error("[GenerateFileVisitor::getFinalReturnBody] Could not find terminator in basic block: {}", bbLabel);
        return returnBody;
    }

    if(auto* retInst = llvm::dyn_cast<llvm::ReturnInst> (terminator))
    {
        auto retVal = retInst->getReturnValue();
        if(retVal == nullptr)
        {
            logger->error("[GenerateFileVisitor::getFinalReturnBody] Could not find return value in basic block: {}", bbLabel);
            return returnBody;
        }

        // set return value with the instruction value
        returnBody += utils::CodeGenUtils::llvmValueToString(retVal);

        // if we are able to find a phi node in the basic block, then we need to replace the return value with the
        // last phi node value from the last pair <bbLabel, value>.
        for(auto& inst: *basicBlock)
        {
            if(inst.getOpcode() != llvm::Instruction::PHI)
            {
                continue;
            }

            auto* phiNode = llvm::dyn_cast<llvm::PHINode>(&inst);
            auto phiNodeHandler = codeGen::ast::PHINodeHandler(llvmFun);
            auto labelAndValuesVec = phiNodeHandler.getLabelsAndValueFromPhiNode(phiNode);
            assert(!labelAndValuesVec.empty() && "Phi node should have at least one pair <bbLabel, value> in it");

            logger->info("[GenerateFileVisitor::getFinalReturnBody] Found phi node in last bb for final return with value: {}", labelAndValuesVec.back().second);
            returnBody = "return " + labelAndValuesVec.back().second;
        }
    }

    return returnBody;
}

void codeGen::ast::GenerateFileVisitor::replaceVarsThatNeedToBeReplacedAtEnd() {
    std::for_each(variablesToBeReplacedAtTheEnd.begin(), variablesToBeReplacedAtTheEnd.end(), [this](auto& pLabelAndValue){
        auto& [instrLabel, value] = pLabelAndValue;
        // replace all occurrences of the variable in the output
        for(auto& [bbLabel, vec]: output)
        {
            for(auto& line: vec)
            {
                // we need to add a space before the variable name to avoid replacing variables that are substrings of other variables
                // e.g. we want to replace "lvar1" with "lvar2" but we don't want to replace "lvar11" with "lvar2"
                std::size_t pos = line.find(" " + instrLabel);
                if(pos != std::string::npos)
                {
                    if(line.size() > pos + 1 + instrLabel.size())
                    {
                        auto nextChar = line[pos + 1 + instrLabel.size()];
                        if(std::isdigit(nextChar))
                        {
                            continue;
                        }
                    }

                }
                // add check for lvar11 found while looking for lvar1
                if(pos != std::string::npos)
                {
                    line.replace(pos, instrLabel.size() + 1, value);
                }
            }
        }
    });
}

void codeGen::ast::GenerateFileVisitor::sanitizeReturnValuesForVoidTypeFunctions() {
    // we need to return "return;" for void type functions but also keep the indentation
    if(!llvmFun.getReturnType()->isVoidTy())
    {
        return;
    }

    for(auto& [bbLabel, vec]: output)
    {
        for(auto& line: vec)
        {
            std::size_t pos = line.find("return");
            if(pos != std::string::npos)
            {
                auto returnIndentation = utils::CodeGenUtils::getSpaces(pos);
                line = returnIndentation + "return;";
            }
        }
    }
}

