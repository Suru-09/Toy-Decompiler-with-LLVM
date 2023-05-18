#include "codeGen/ast/GenerateFileVisitor.h"
#include "logger/LoggerManager.h"

#include "codeGen/ast/LlvmFunctionNode.h"
#include "codeGen/ast/LlvmBasicBlockNode.h"
#include "codeGen/ast/LlvmInstructionNode.h"
#include "codeGen/BracketManager.h"
#include "codeGen/DefineVariablesHandler.h"
#include "codeGen/BranchConditionalGen.h"

#include "utils/CodeGenUtils.h"


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
    logger->info("[GenerateFileVisistor] Instruction name: {}, body: {}", node->getName(), node->getInstructionBody());

    auto instr = utils::CodeGenUtils::getInstructionAfterLabel(llvmFun, nodeName);
    if(!instr)
    {
        logger->error("[GenerateFileVisistor] Failed to get LLVM instruction after label: {}", nodeName);
        return std::make_pair<std::string, std::string>(node->getName(), "");
    }

    // ignore phi nodes instructions, they are handled separately.
    if(instr->getOpcode() == llvm::Instruction::PHI)
    {
        logger->info("[GenerateFileVisistor] Skipping PHI node instruction: {}", nodeName);
        return std::make_pair<std::string, std::string>(node->getName(), "");
    }

    // Only print terminator instructions if they have multiple uses.
    // Why? Because they are usually conditions for loops/ifs and there is no need
    // to print them twice if they are not used anywhere else.
    auto terminatorName = utils::CodeGenUtils::getTerminatorAlias(llvmFun, instr);
    logger->info("[GenerateFileVisistor] Terminator name: {} and node name: {}", terminatorName, nodeName);
    if(nodeName == terminatorName && utils::CodeGenUtils::doesInstructionHaveSingleUse(instr))
    {
        logger->info("[GenerateFileVisistor] Skipping printing for the node: {}", nodeName);
        return std::make_pair<std::string, std::string>(node->getName(), "");
    }

    auto indentation = utils::CodeGenUtils::getSpaces(indentationLevel);
    output[lastBasicBlockName].push_back(indentation +  node->getInstructionBody());

    return std::make_pair<std::string, std::string>(node->getName(), "");
}

std::pair<std::string, std::string> codeGen::ast::GenerateFileVisitor::visit(std::shared_ptr<LlvmBasicBlockNode> node) {
    output.emplace(node->getName(), std::vector<std::string>());
    logger->info("[GenerateFileVisistor] Basic block being processed: <{}>", node->getName());
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
    }

    for(auto &child: node->getChildren()) {
        auto [name, code] = visit(std::dynamic_pointer_cast<LlvmInstructionNode>(child));
    }

    auto searchInstrValue = [&](const std::string& instrName){
        logger->info("[GenerateFileVisitor] Searching for instruction: {}", instrName);
        auto val = std::dynamic_pointer_cast<LlvmInstructionNode> (node->getChildren().front());
        if(val)
        {
            logger->info("[GenerateFileVisitor] Found instruction: {}, with value: {}", val->getName(), val->getInstructionBody());
            return val->getInstructionBody();
        }
        return std::string();
    };

    if(codeGen::BracketManager::isLoop(bbInfo) == udm::BBInfo::LoopType::WHILE
        || codeGen::BracketManager::isLoop(bbInfo) == udm::BBInfo::LoopType::DO_WHILE
    )
    {
        codeGen::BracketManager::addBracket(node->getName(), funcInfo);
        auto space = utils::CodeGenUtils::getSpaces(indentationLevel);
        auto condition = utils::CodeGenUtils::getTerminatorCondition(llvmFun, node->getName());
        auto condStr = searchInstrValue(condition).empty() ? "true" : searchInstrValue(condition);
        output[lastBasicBlockName].push_back(space + "while (" + condStr + ") {");
        indentationLevel += 4;
    }

    if(codeGen::BracketManager::isConditional(bbInfo))
    {
        codeGen::BracketManager::addBracket(node->getName(), funcInfo);
        auto space = utils::CodeGenUtils::getSpaces(indentationLevel);
        auto condition = utils::CodeGenUtils::getTerminatorCondition(llvmFun, node->getName());
        auto condStr = searchInstrValue(condition).empty()  ? "true" : searchInstrValue(condition);
        output[lastBasicBlockName].push_back(space + "if (" + condStr + ") {");
        indentationLevel += 4;
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

void codeGen::ast::GenerateFileVisitor::setOutputFilename(const std::string &filename) {
    outputFilename = filename;
}

std::string codeGen::ast::GenerateFileVisitor::getOutputFilename() const {
    return outputFilename;
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

