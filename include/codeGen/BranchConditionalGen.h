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
    
    static std::string generateConditional(std::shared_ptr<Instruction> instr, bool isElseIf = false);
};

}   // namespace codeGen

#endif