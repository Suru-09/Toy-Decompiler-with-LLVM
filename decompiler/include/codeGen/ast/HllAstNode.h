#ifndef REVERSE_ENGINEERING_TOOL_HLLASTNODE_H
#define REVERSE_ENGINEERING_TOOL_HLLASTNODE_H

#include <vector>
#include <string>
#include <memory>

namespace codeGen::ast {

class HllAstNodeVisitor;

class HllAstNode {
public:
    HllAstNode() = default;
    virtual ~HllAstNode() = default;

    std::vector<std::shared_ptr<HllAstNode>> getChildren() const;

    void addChild(const std::shared_ptr<HllAstNode>& child);

protected:
    virtual std::pair<std::string, std::string> accept(std::shared_ptr<HllAstNodeVisitor> visitor) = 0;
private:
    std::vector<std::shared_ptr<HllAstNode>> children;
};

    void addPhiNodesValues(const std::pair<std::string, std::string> &phiNode);
}   // namespace codeGen::ast

#endif //REVERSE_ENGINEERING_TOOL_HLLASTNODE_H


