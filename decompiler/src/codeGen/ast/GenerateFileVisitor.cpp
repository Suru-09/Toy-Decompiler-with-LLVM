#include "codeGen/ast/GenerateFileVisitor.h"
#include "logger/LoggerManager.h"

#include "codeGen/ast/LlvmFunctionNode.h"
#include "codeGen/ast/LlvmBasicBlockNode.h"
#include "codeGen/ast/LlvmInstructionNode.h"
#include "utils/CodeGenUtils.h"
#include "codeGen/BracketManager.h"

std::pair<std::string, std::string> codeGen::ast::GenerateFileVisitor::visit(std::shared_ptr<LlvmFunctionNode> node) {
    // Iterate over all basic blocks and instructions and generate the LLVM IR code.
    for(auto &child: node->getChildren()) {
        auto [name, code] = visit(std::dynamic_pointer_cast<LlvmBasicBlockNode>(child));
        logger->info("Basic block name: {}", name);
    }
    return std::make_pair<std::string, std::string>(node->getName(), "");
}

std::pair<std::string, std::string>
codeGen::ast::GenerateFileVisitor::visit(std::shared_ptr<LlvmInstructionNode> node) {
    auto nodeName = node->getName();
    for(auto &child: node->getChildren()) {
        auto childPtr = std::dynamic_pointer_cast<LlvmInstructionNode>(child);
        assert(childPtr != nullptr);
        auto [name, code] = visit(childPtr);
        logger->info("[GenerateFileVisistor] Instruction name: {}, body: {}", name, childPtr->getInstructionBody());

        if (childPtr->getOpcode() == llvm::Instruction::PHI)
        {
            // Extract the labels and values from the PHI instruction.
            const std::string phiNodeStr = childPtr->getInstructionBody();
            auto labels = utils::CodeGenUtils::extractLabelsFromPhiString(phiNodeStr);
            auto values = utils::CodeGenUtils::extractValuesFromPhiString(phiNodeStr);
            assert(labels.size() == values.size());
            for (int i = 0; i < labels.size(); i++)
            {
                auto indentation = utils::CodeGenUtils::getSpaces(indentationLevel);
                auto strValue = indentation + utils::CodeGenUtils::extractPhiNodeLeftValue(phiNodeStr) + " = " + values[i];
                logger->info("[GenerateFileVisistor] Label -> {}, Value -> {}", labels[i], strValue);
                addPhiNodesValues(std::make_pair<std::string, std::string>(std::move(labels[i]), std::move(strValue)));
            }
            continue;
        }
        auto indentation = utils::CodeGenUtils::getSpaces(indentationLevel);
        output[lastBasicBlockName].push_back(indentation +  childPtr->getInstructionBody());
    }

    // same thing as above but only for node
    logger->info("[GenerateFileVisistor] Instruction name: {}, body: {}", node->getName(), node->getInstructionBody());

    if (node->getOpcode() == llvm::Instruction::PHI)
    {
        // Extract the labels and values from the PHI instruction.
        const std::string phiNodeStr = node->getInstructionBody();
        auto labels = utils::CodeGenUtils::extractLabelsFromPhiString(phiNodeStr);
        auto values = utils::CodeGenUtils::extractValuesFromPhiString(phiNodeStr);
        logger->info("[GenerateFileVisistor] Phi nodes size: {}", labels.size());
        assert(labels.size() == values.size());
        for (int i = 0; i < labels.size(); i++)
        {
            auto indentation = utils::CodeGenUtils::getSpaces(indentationLevel);
            auto strValue = indentation + utils::CodeGenUtils::extractPhiNodeLeftValue(phiNodeStr) + " = " + values[i];
            logger->info("[GenerateFileVisistor] Label -> {}, Value -> {}", labels[i], strValue);
            addPhiNodesValues(std::make_pair<std::string, std::string>(std::move(labels[i]), std::move(strValue)));
        }
    }
    else {
        auto indentation = utils::CodeGenUtils::getSpaces(indentationLevel);
        output[lastBasicBlockName].push_back(indentation +  node->getInstructionBody());
    }


    return std::make_pair<std::string, std::string>(node->getName(), "");
}

std::pair<std::string, std::string> codeGen::ast::GenerateFileVisitor::visit(std::shared_ptr<LlvmBasicBlockNode> node) {
    output.emplace(node->getName(), std::vector<std::string>());
    logger->info("[GenerateFileVisistor] Basic block being processed: <{}>", node->getName());
    lastBasicBlockName = node->getName();
    auto bbInfo = funcInfo.getBBInfo(lastBasicBlockName);

    while(codeGen::BracketManager::shouldCloseConditional(node->getName(), funcInfo))
    {
        indentationLevel -= 4;
        auto space = utils::CodeGenUtils::getSpaces(indentationLevel);
        output[lastBasicBlockName].push_back(space + "}");
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
        auto condition = utils::CodeGenUtils::getLoopCondition(llvmFun, node->getName());
        auto condStr = condition.empty() ? "true" : condition;
        output[lastBasicBlockName].push_back(space + "while (" + condStr + ") {");
        indentationLevel += 4;
    }

    if(codeGen::BracketManager::isConditional(bbInfo))
    {
        codeGen::BracketManager::addBracket(node->getName(), funcInfo);
        auto space = utils::CodeGenUtils::getSpaces(indentationLevel);
        auto condition = utils::CodeGenUtils::getLoopCondition(llvmFun, node->getName());
        auto condStr = condition.empty() ? "true" : condition;
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

void codeGen::ast::GenerateFileVisitor::setOutputFilename(const std::string &filename) {
    outputFilename = filename;
}

std::string codeGen::ast::GenerateFileVisitor::getOutputFilename() const {
    return outputFilename;
}

codeGen::ast::GenerateFileVisitor::GenerateFileVisitor(llvm::Function& fun)
: indentationLevel(0), llvmFun(fun)
{
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

