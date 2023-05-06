#ifndef REVERSE_ENGINEERING_TOOL_LLVMBASICBLOCKNODE_H
#define REVERSE_ENGINEERING_TOOL_LLVMBASICBLOCKNODE_H

#include <string>
#include <memory>
#include <spdlog/spdlog.h>

#include "codeGen/ast/HllAstNode.h"
#include "codeGen/ast/HllAstNodeVisitor.h"

namespace codeGen::ast {

class LlvmBasicBlockNode : public HllAstNode, public std::enable_shared_from_this<LlvmBasicBlockNode> {
public:
    explicit LlvmBasicBlockNode(const std::string& name);
    ~LlvmBasicBlockNode() override = default;
    std::pair<std::string, std::string> accept(std::shared_ptr<HllAstNodeVisitor> visitor) override;
    std::string getName() const;
private:
    std::string name;
    std::shared_ptr<spdlog::logger> logger;
};

}   // namespace codeGen::ast


#endif //REVERSE_ENGINEERING_TOOL_LLVMBASICBLOCKNODE_H
