#ifndef _OTHER_INSTRUCTION_H_
#define _OTHER_INSTRUCTION_H_

#include "codeGen/instructions/Instruction.h"

#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Instructions.h>


namespace codeGen {

class OtherInstruction : public codeGen::Instruction {
public:
    OtherInstruction(llvm::Instruction& inst, int numSpaces);
    ~OtherInstruction() = default;

    std::string toString() override;

private:
    std::string handleCmpInst(llvm::CmpInst* cmpInst, int numSpaces);
    std::string handleIntCmpInst(llvm::CmpInst* cmpInst);
    std::string handleFPCmpInst(llvm::CmpInst* cmpInst);

    std::string handlePhiNode(llvm::PHINode* phiNode);
    std::string handleSelectInst(llvm::SelectInst* selectInst);
};

}   // namespace codeGen

#endif