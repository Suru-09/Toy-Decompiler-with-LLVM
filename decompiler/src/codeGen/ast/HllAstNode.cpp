#include "codeGen/ast/HllAstNode.h"

void codeGen::ast::HllAstNode::addChild(const std::shared_ptr<HllAstNode>& child) {
    children.push_back(child);
}

std::vector<std::shared_ptr<codeGen::ast::HllAstNode>> codeGen::ast::HllAstNode::getChildren() const {
    return children;
}
