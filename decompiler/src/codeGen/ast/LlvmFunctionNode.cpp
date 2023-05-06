#include "codeGen/ast/LlvmFunctionNode.h"
#include "logger/LoggerManager.h"

codeGen::ast::LlvmFunctionNode::LlvmFunctionNode(const std::string &name)
: name(name)
{
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}

std::pair<std::string, std::string> codeGen::ast::LlvmFunctionNode::accept(std::shared_ptr<HllAstNodeVisitor> visitor) {
    return visitor->visit(shared_from_this());
}

std::string codeGen::ast::LlvmFunctionNode::getName() const {
    return name;
}


