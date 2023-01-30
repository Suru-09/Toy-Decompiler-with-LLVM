#ifndef _CONVERSION_INSTRUCTION_H_
#define _CONVERSION_INSTRUCTION_H_

#include "codeGen/instructions/Instruction.h"


namespace codeGen {

class ConversionInstruction : public codeGen::Instruction {
public:
    ConversionInstruction(llvm::Instruction& inst);
    ~ConversionInstruction() = default;

    std::string toString() override;
};

}  // namespace codeGen

#endif