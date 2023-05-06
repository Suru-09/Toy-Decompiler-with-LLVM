#include "codeGen/ast/LlvmInstructionNode.h"
#include "logger/LoggerManager.h"

codeGen::ast::LlvmInstructionNode::LlvmInstructionNode(const std::string &name)
: name(name)
{
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}

std::pair<std::string, std::string> codeGen::ast::LlvmInstructionNode::accept(std::shared_ptr<HllAstNodeVisitor> visitor) {
    return visitor->visit(shared_from_this());
}

void codeGen::ast::LlvmInstructionNode::setOpcode(unsigned int opcode) {
    this->opcode = opcode;
}

void codeGen::ast::LlvmInstructionNode::setInstructionBody(const std::string &instructionBody) {
    this->instructionBody = instructionBody;
}

unsigned int codeGen::ast::LlvmInstructionNode::getOpcode() const {
    return opcode;
}

std::string codeGen::ast::LlvmInstructionNode::getInstructionBody() const {
    return instructionBody;
}

std::string codeGen::ast::LlvmInstructionNode::getName() const {
    return name;
}

