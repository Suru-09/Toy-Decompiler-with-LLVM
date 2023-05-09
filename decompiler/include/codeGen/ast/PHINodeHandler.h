#ifndef REVERSE_ENGINEERING_TOOL_PHINODEHANDLER_H
#define REVERSE_ENGINEERING_TOOL_PHINODEHANDLER_H

#include <string>
#include <memory>
#include <vector>
#include <spdlog/spdlog.h>

#include <llvm/IR/Instructions.h>
#include <llvm/IR/Function.h>

#include "codeGen/ast/StackVarAlias.h"

namespace codeGen::ast
{

class PHINodeHandler {
public:
    explicit PHINodeHandler(llvm::Function& llvmFun);

    std::vector<StackVarAlias> getPHINodeAliases();

private:
    llvm::Function& m_llvmFun;
    std::shared_ptr<spdlog::logger> logger;

private:
    std::vector<std::pair<std::string, std::string>> getLabelsAndValueFromPhiNode(llvm::PHINode* phiNode);
};

}   // namespace codeGen, ast

#endif //REVERSE_ENGINEERING_TOOL_PHINODEHANDLER_H
