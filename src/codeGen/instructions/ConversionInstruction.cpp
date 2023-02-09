#include "codeGen/instructions/ConversionInstruction.h"
#include "utils/CodeGenUtils.h"

#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include "llvm/IR/InstrTypes.h"

codeGen::ConversionInstruction::ConversionInstruction(llvm::Instruction& inst, int numSpaces) {
    if(llvm::CastInst* castOp = llvm::dyn_cast<llvm::CastInst>(&inst))
    {
        // auto sourceType = castOp->getSrcTy();
        // instructionString += utils::CodeGenUtils::typeToString(sourceType->getTypeID()) + " ";
        // instructionString += inst.getName().str() + " = (";

        instructionString += " ( ";
        auto destType = castOp->getDestTy();
        instructionString += utils::CodeGenUtils::typeToString(destType) + ") ";
        
        // auto operand = castOp->getOperand(0);
        // std::string name = operand->getName().str();
        // instructionString += name + " ";
    }
}

std::string codeGen::ConversionInstruction::toString() {
    return instructionString;
}