#ifndef _BINARY_INSTRUCTION_H_
#define _BINARY_INSTRUCTION_H_

#include <iostream>

#include "codeGen/instructions/Instruction.h"

namespace codeGen {

class BinaryInstruction : public codeGen::Instruction {
public:
    BinaryInstruction(llvm::Instruction& inst, int numSpaces);
    ~BinaryInstruction() = default;

    std::string toString() override;
};

}   // namespace codeGen


#endif