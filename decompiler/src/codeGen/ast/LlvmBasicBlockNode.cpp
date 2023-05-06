#include "codeGen/ast/LlvmBasicBlockNode.h"
#include "logger/LoggerManager.h"

codeGen::ast::LlvmBasicBlockNode::LlvmBasicBlockNode(const std::string &name)
: name(name)
{
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}

std::pair<std::string, std::string> codeGen::ast::LlvmBasicBlockNode::accept(std::shared_ptr<HllAstNodeVisitor> visitor) {
    return visitor->visit(shared_from_this());
}

std::string codeGen::ast::LlvmBasicBlockNode::getName() const {
    return name;
}
