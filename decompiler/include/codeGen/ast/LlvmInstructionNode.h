#ifndef REVERSE_ENGINEERING_TOOL_LLVMINSTRUCTIONNODE_H
#define REVERSE_ENGINEERING_TOOL_LLVMINSTRUCTIONNODE_H

#include <string>
#include <memory>
#include <vector>
#include <spdlog/spdlog.h>

#include "HllAstNode.h"
#include "HllAstNodeVisitor.h"

namespace codeGen::ast {

class LlvmInstructionNode : public HllAstNode, public std::enable_shared_from_this<LlvmInstructionNode> {
public:
    explicit LlvmInstructionNode(const std::string& name);
    ~LlvmInstructionNode() override = default;
    std::pair<std::string, std::string> accept(std::shared_ptr<HllAstNodeVisitor> visitor) override;

    void setOpcode(unsigned int opcode);
    void setInstructionBody(const std::string& instructionBody);

    unsigned int getOpcode() const;
    std::string getInstructionBody() const;
    std::string getName() const;
private:
    std::string name;
    unsigned int opcode;
    std::string instructionBody;
    std::shared_ptr<spdlog::logger> logger;
};

}   // namespace codeGen::ast


#endif //REVERSE_ENGINEERING_TOOL_LLVMINSTRUCTIONNODE_H
