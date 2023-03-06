#ifndef _BRANCH_CONDITIONAL_GEN_H_
#define _BRANCH_CONDITIONAL_GEN_H_

#include <iostream>
#include <memory>

#include "codeGen/instructions/Instruction.h"

namespace codeGen {

class BranchConditionalGen {
public:
    BranchConditionalGen() = default;
    ~BranchConditionalGen() = default;
    
    static std::string generateConditional(const std::string& condition, int numSpaces, bool isElseIf = false);
};

}   // namespace codeGen

#endif