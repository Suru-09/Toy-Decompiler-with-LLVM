#ifndef _UNARY_INSTRUCTION_H_
#define _UNARY_INSTRUCTION_H_

#include "codeGen/instructions/Instruction.h"

namespace codeGen{

class UnaryInstruction : public codeGen::Instruction {
public:
    UnaryInstruction(llvm::Instruction& inst);
    ~UnaryInstruction() = default;

    std::string toString() override;
};

}   // namespace codeGen

#endif