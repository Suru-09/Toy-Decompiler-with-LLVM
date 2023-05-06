#include "codeGen/ast/GenerateFileVisitor.h"
#include "logger/LoggerManager.h"

#include "codeGen/ast/LlvmFunctionNode.h"
#include "codeGen/ast/LlvmBasicBlockNode.h"
#include "codeGen/ast/LlvmInstructionNode.h"
#include "utils/CodeGenUtils.h"

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
    for(auto &child: node->getChildren()) {
        auto childPtr = std::dynamic_pointer_cast<LlvmInstructionNode>(child);
        assert(childPtr != nullptr);
        auto [name, code] = visit(childPtr);
        logger->info("Instruction name: {}, body: {}", name, childPtr->getInstructionBody());

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
                logger->info("Label -> {}, Value -> {}", labels[i], strValue);
                addPhiNodesValues(std::make_pair<std::string, std::string>(std::move(labels[i]), std::move(strValue)));
            }
            continue;
        }
        auto indentation = utils::CodeGenUtils::getSpaces(indentationLevel);
        output[lastBasicBlockName].push_back(indentation +  childPtr->getInstructionBody());

    }
    return std::make_pair<std::string, std::string>(node->getName(), "");
}

std::pair<std::string, std::string> codeGen::ast::GenerateFileVisitor::visit(std::shared_ptr<LlvmBasicBlockNode> node) {
    output.emplace(node->getName(), std::vector<std::string>());
    logger->info("Basic block being processed: <{}>", node->getName());
    lastBasicBlockName = node->getName();

    auto bbInfo = funcInfo.getBBInfo(lastBasicBlockName);
    if (utils::CodeGenUtils::isLoop(funcInfo, lastBasicBlockName))
    {
        // Add the loop header.
        output[lastBasicBlockName].push_back(
                "while(" + utils::CodeGenUtils::getLoopCondition(llvmFun, lastBasicBlockName) + ") {"
        );
        indentationLevel += 4;
        inLoop = true;
    }
    else if(inLoop && !bbInfo.getIsLoop())
    {
        inLoop = false;
        while (indentationLevel > 0)
        {
            indentationLevel -= 4;
            std::string spaces = utils::CodeGenUtils::getSpaces(indentationLevel);
            output[lastBasicBlockName].push_back( spaces + "}\n");
        }
        indentationLevel = 0;
    }

    // check for IF statements
    if(!bbInfo.getFollowNode().empty() && bbInfo.getLoopType() == udm::BBInfo::LoopType::NONE)
    {
        // Add the if statement.
        std::string spaces = utils::CodeGenUtils::getSpaces(indentationLevel);
        output[lastBasicBlockName].push_back(
                spaces + "if(" + utils::CodeGenUtils::getLoopCondition(llvmFun, lastBasicBlockName) + ") {"
        );
        indentationLevel += 4;
    }


    for(auto &child: node->getChildren()) {
        auto [name, code] = visit(std::dynamic_pointer_cast<LlvmInstructionNode>(child));
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
    output[bbStr].push_back(value);
}

