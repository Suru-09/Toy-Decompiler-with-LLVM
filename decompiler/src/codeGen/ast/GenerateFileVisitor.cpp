
#include "codeGen/ast/GenerateFileVisitor.h"
#include "logger/LoggerManager.h"

#include "codeGen/ast/LlvmFunctionNode.h"
#include "codeGen/ast/LlvmBasicBlockNode.h"
#include "codeGen/ast/LlvmInstructionNode.h"
#include "codeGen/BracketManager.h"
#include "codeGen/DefineVariablesHandler.h"
#include "codeGen/BranchConditionalGen.h"
#include "settings/CodegenSettings.h"
#include "utils/CodeGenUtils.h"
#include "codeGen/GenerateFnHeader.h"

#include <llvm/ADT/PostOrderIterator.h>
#include <llvm/Analysis/PostDominators.h>
#include "llvm/IR/Type.h"
#include "llvm/Support/Casting.h"

#include <filesystem>
#include <fstream>


std::pair<std::string, std::string> codeGen::ast::GenerateFileVisitor::visit(std::shared_ptr<LlvmFunctionNode> node) {
    // Iterate over all basic blocks and instructions and generate the LLVM IR code.
    for(auto &child: node->getChildren()) {
        auto [name, code] = visit(std::dynamic_pointer_cast<LlvmBasicBlockNode>(child));
        logger->info("Basic block name: {}", name);
    }

    // !!!!! Replace stack variables with their aliases at the end of everything.
    replaceStackVarWithAlias(PHINodeHandler{llvmFun}.getPHINodeAliases());
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

    if(instr->getOpcode() == llvm::Instruction::Ret)
    {
        auto returnBody = getFinalReturnBody(lastBasicBlockName);
        logger->info("[GenerateFileVisitor::visit(InstructionNode)] Found return value from last basic block: {}", nodeName);
        output[lastBasicBlockName].push_back(utils::CodeGenUtils::getSpaces(indentationLevel) + returnBody);
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

    auto indentation = utils::CodeGenUtils::getSpaces(indentationLevel);
    output[lastBasicBlockName].push_back(indentation +  node->getInstructionBody());

    return std::make_pair<std::string, std::string>(node->getName(), "");
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

    while(codeGen::BracketManager::shouldCloseConditional(node->getName(), funcInfo))
    {
        indentationLevel -= 4;
        auto space = utils::CodeGenUtils::getSpaces(indentationLevel);
        output[lastBasicBlockName].push_back(space + "}");
        logger->info("[GenerateFileVisitor::visit(BasicBlock)] Closing conditional for basic block: {}", node->getName());
    }

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
        codeGen::BracketManager::addBracket(node->getName(), funcInfo);
        auto space = utils::CodeGenUtils::getSpaces(indentationLevel);

        auto branchingToTerminalBlock = utils::CodeGenUtils::checkIfCurrentBlockBranchesToTerminalBlock(llvmFun, node->getName());
        logger->info("[GenerateFileVisitor::visit(BasicBlock)] Branching to terminal block result: <{}, {}>", branchingToTerminalBlock.isBranchingToTerminalBlock, branchingToTerminalBlock.isConditionReversed);
        if (branchingToTerminalBlock.isBranchingToTerminalBlock)
        {
            //codeGen::BracketManager::handleBracketsWhenAddingReturn(node->getName(), funcInfo, llvmFun);
        }

        auto condition = utils::CodeGenUtils::getTerminatorCondition(llvmFun, node->getName());
        auto conditionBody = utils::CodeGenUtils::getBranchInstrBodyGivenBlock(llvmFun, condition.first);
        conditionBody = utils::CodeGenUtils::extractLHSFromInstructionBody(conditionBody);\
        // really ugly hack to handle the case when the condition is reversed.
        //conditionBody = !conditionBody.empty() && branchingToTerminalBlock.isConditionReversed ? "!(" + conditionBody + ")" : conditionBody;

        auto condStr = conditionBody.empty()  ? "true" : conditionBody;

        output[lastBasicBlockName].push_back(space + "while (" + condStr + ") {");
        indentationLevel += 4;
    }

    if(codeGen::BracketManager::isConditional(bbInfo))
    {
        codeGen::BracketManager::addBracket(node->getName(), funcInfo);
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
        conditionBody = !conditionBody.empty() && branchToTerminalBlockResult.isConditionReversed ? "!(" + conditionBody + ")" : conditionBody;

        auto condStr = conditionBody.empty()  ? "true" : conditionBody;

        output[lastBasicBlockName].push_back(space + "if (" + condStr + ") {");
        indentationLevel += 4;
        if(branchToTerminalBlockResult.isBranchingToTerminalBlock)
        {
            logger->info("[GenerateFileVisitor::visit(BasicBlock)] Adding return value for conditional block: {}", node->getName());
            addReturnValue(node->getName());
        }
    }

    while(codeGen::BracketManager::shouldCloseLoop(node->getName(), funcInfo))
    {
        indentationLevel -= 4;
        auto space = utils::CodeGenUtils::getSpaces(indentationLevel);
        output[lastBasicBlockName].push_back(space + "}");
    }

    return std::make_pair<std::string, std::string>(node->getName(), "");
}

void codeGen::ast::GenerateFileVisitor::addVariablesDefinitions() {
    for(auto [key, vec]: definedVariables)
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
            if(bbKey == alias.getBasicBlockName())
            {
                std::string line = vec[i];
                std::size_t pos = line.find(alias.getStackVarName());
                if(pos != std::string::npos)
                {
                    std::string oldVal = line.substr(pos, alias.getStackVarName().size());
                    logger->info("[GenerateFileVisitor::replaceOneStackVarWithAlias] Found stack var: {} in line: {}, replacing old value: {}", alias.getStackVarName(), line, oldVal);
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

    llvm::ReversePostOrderTraversal<llvm::Function*> rpot(&llvmFun);
    for(auto &bb: rpot)
    {
        auto key = bb->getName().str();
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
            if(labelAndValuesVec.empty())
            {
                logger->error("[GenerateFileVisitor::getFinalReturnBody] Could not find labels and values from phi node in basic block: {}", bbLabel);
                return returnBody;
            }

            returnBody = "return " + labelAndValuesVec.back().second;
        }
    }

    return returnBody;
}

