#include "codeGen/instructions/TerminatorInstruction.h"
#include "utils/CodeGenUtils.h"

codeGen::TerminatorInstruction::TerminatorInstruction(llvm::Instruction& inst, int numSpaces) {
    bool printLhs = utils::CodeGenUtils::canAssignTo(&inst);
    if(printLhs)
    {
        instructionString += inst.getName().str() + " = ";
    }

    if(auto* branchOp = llvm::dyn_cast<llvm::BranchInst>(&inst)) {
        if(branchOp->isConditional()) {
            instructionString += branchOp->getCondition()->getName().str(); 
        }
    }

    if(auto* returnOp = llvm::dyn_cast<llvm::ReturnInst>(&inst)) {
        instructionString += std::string(numSpaces, ' ');
        instructionString += "ret ";
        if(returnOp->getReturnValue()) {
            instructionString += returnOp->getReturnValue()->getName();
        }
    }

}

std::string codeGen::TerminatorInstruction::toString() {
    return instructionString;
}