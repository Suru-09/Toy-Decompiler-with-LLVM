#include "codeGen/instructions/ConversionInstruction.h"
#include "utils/CodeGenUtils.h"

#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/InstrTypes.h>

codeGen::ConversionInstruction::ConversionInstruction(llvm::Instruction& inst, int numSpaces) {
    bool printLhs = utils::CodeGenUtils::canAssignTo(&inst);
    if(printLhs)
    {
        instructionString += inst.getName().str() + " = ";
    }
    if(llvm::CastInst* castOp = llvm::dyn_cast<llvm::CastInst>(&inst))
    {
        if(auto sextInstr = llvm::dyn_cast<llvm::SExtInst>(&inst))
        {
            instructionString += inst.getOperand(0)->getName().str();
        }
        else
        {
            instructionString += " (";
            auto destType = castOp->getDestTy();
            instructionString += utils::CodeGenUtils::typeToString(destType) + ")";
            
            auto operand = castOp->getOperand(0);
            std::string name = operand->getName().str();
            instructionString += name;
        }

        
    }
}

std::string codeGen::ConversionInstruction::toString() {
    return instructionString;
}