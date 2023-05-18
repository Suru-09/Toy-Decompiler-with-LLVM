#ifndef _BRANCH_CONDITIONAL_GEN_H_
#define _BRANCH_CONDITIONAL_GEN_H_

#include <iostream>
#include <memory>
#include <unordered_map>

#include "codeGen/instructions/Instruction.h"

namespace codeGen {

class BranchConditionalGen {
public:
    BranchConditionalGen() = default;
    ~BranchConditionalGen() = default;
    
    static std::string generateConditional(const std::string& condition, int numSpaces, bool isElseIf = false);
    [[nodiscard]] static std::unordered_map<std::string, std::string> collectExpansionRequiredTerminatorInstructions(const llvm::Function& func);
};

}   // namespace codeGen

#endif