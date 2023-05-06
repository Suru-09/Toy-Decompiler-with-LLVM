#ifndef REVERSE_ENGINEERING_TOOL_HLLASTNODEVISITOR_H
#define REVERSE_ENGINEERING_TOOL_HLLASTNODEVISITOR_H

#include <string>

#include "codeGen/ast/LlvmFunctionNode.h"

namespace codeGen::ast {

// Forward declaration of all AST nodes to avoid circular dependencies.
class LlvmFunctionNode;
class LlvmInstructionNode;
class LlvmBasicBlockNode;

class HllAstNodeVisitor {
public:
    HllAstNodeVisitor() = default;
    virtual ~HllAstNodeVisitor() = default;

    virtual std::pair<std::string, std::string> visit(std::shared_ptr<LlvmFunctionNode> node) = 0;
    virtual std::pair<std::string, std::string> visit(std::shared_ptr<LlvmInstructionNode> node) = 0;
    virtual std::pair<std::string, std::string> visit(std::shared_ptr<LlvmBasicBlockNode> node) = 0;
};
}   // namespace codeGen::ast

#endif //REVERSE_ENGINEERING_TOOL_HLLASTNODEVISITOR_H
