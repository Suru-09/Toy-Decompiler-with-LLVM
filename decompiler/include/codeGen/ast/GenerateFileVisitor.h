#ifndef REVERSE_ENGINEERING_TOOL_GENERATEFILEVISITOR_H
#define REVERSE_ENGINEERING_TOOL_GENERATEFILEVISITOR_H

#include <string>
#include <memory>
#include <spdlog/spdlog.h>

#include "codeGen/ast/HllAstNodeVisitor.h"
#include "udm/FuncInfo.h"

namespace codeGen::ast {

// forward declarations
class LlvmFunctionNode;
class LlvmInstructionNode;
class LlvmBasicBlockNode;


class GenerateFileVisitor : public HllAstNodeVisitor {
public:
    explicit GenerateFileVisitor(llvm::Function& f);
    ~GenerateFileVisitor() override = default;

    std::pair<std::string, std::string> visit(std::shared_ptr<LlvmFunctionNode> node) override;
    std::pair<std::string, std::string> visit(std::shared_ptr<LlvmInstructionNode> node) override;
    std::pair<std::string, std::string> visit(std::shared_ptr<LlvmBasicBlockNode> node) override;

    void setOutputFilename(const std::string& filename);
    void setFuncInfo(const udm::FuncInfo& funcInfo);

    udm::FuncInfo getFuncInfo() const;
    std::string getOutputFilename() const;
    std::unordered_map<std::string, std::vector<std::string>> getOutput() const;
private:
    std::unordered_map<std::string, std::vector<std::string>> output;
    std::string outputFilename;
    std::string lastBasicBlockName;
    unsigned int indentationLevel;
    bool inLoop;
    udm::FuncInfo funcInfo;
    llvm::Function& llvmFun;
    std::shared_ptr<spdlog::logger> logger;
private:
    bool writeToFile(const std::string& filename);
    void addPhiNodesValues(const std::pair<std::string, std::string>& phiNode);
};

}   // namespace codeGen::ast


#endif //REVERSE_ENGINEERING_TOOL_GENERATEFILEVISITOR_H
