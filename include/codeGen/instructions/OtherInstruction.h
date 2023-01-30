#ifndef _OTHER_INSTRUCTION_H_
#define _OTHER_INSTRUCTION_H_

#include "codeGen/instructions/Instruction.h"


namespace codeGen {

class OtherInstruction : public codeGen::Instruction {
public:
    OtherInstruction(llvm::Instruction& inst);
    ~OtherInstruction() = default;

    std::string toString() override;
};

}   // namespace codeGen

#endif