#ifndef _TERMINATOR_INSTRUCTION_H_
#define _TERMINATOR_INSTRUCTION_H_

#include "codeGen/instructions/Instruction.h"

#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Instructions.h>

namespace codeGen {

class TerminatorInstruction : public codeGen::Instruction {
public:
    TerminatorInstruction(llvm::Instruction& inst, int numSpaces);
    ~TerminatorInstruction() = default;

    std::string toString() override;

};

}   // namespace codeGen

#endif