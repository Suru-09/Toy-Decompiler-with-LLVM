#ifndef _BITWISE_BINARY_INSTRUCTION_H_
#define _BITWISE_BINARY_INSTRUCTION_H_

#include "codeGen/instructions/Instruction.h"

namespace codeGen {

class BitwiseBinaryInstruction : public codeGen::Instruction {
public:
    BitwiseBinaryInstruction(llvm::Instruction& inst, int numSpaces);
    ~BitwiseBinaryInstruction() = default;

    std::string toString() override;
};

}   // namespace codeGen


#endif