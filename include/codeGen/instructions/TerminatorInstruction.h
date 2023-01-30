#ifndef _TERMINATOR_INSTRUCTION_H_
#define _TERMINATOR_INSTRUCTION_H_

#include "codeGen/instructions/Instruction.h"

namespace codeGen {

class TerminatorInstruction : public codeGen::Instruction {
public:
    TerminatorInstruction(llvm::Instruction& inst);
    ~TerminatorInstruction() = default;

    std::string toString() override;

};

}   // namespace codeGen

#endif