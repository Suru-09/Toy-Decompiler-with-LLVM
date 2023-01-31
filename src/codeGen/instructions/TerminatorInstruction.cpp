#include "codeGen/instructions/TerminatorInstruction.h"

codeGen::TerminatorInstruction::TerminatorInstruction(llvm::Instruction& inst, int numSpaces) {
    auto printLhs = [&]() {
        instructionString += std::string(numSpaces, ' ');
        instructionString += inst.getOpcodeName();
        instructionString += " ";
    };

    if(llvm::BranchInst* branchOp = llvm::dyn_cast<llvm::BranchInst>(&inst)) {
        if(branchOp->isConditional()) {
            instructionString += branchOp->getCondition()->getName();
        }
    }

    if(llvm::ReturnInst* returnOp = llvm::dyn_cast<llvm::ReturnInst>(&inst)) {
        instructionString += std::string(numSpaces, ' ');
        instructionString += "ret ";
        if(returnOp->getReturnValue()) {
            instructionString += returnOp->getReturnValue()->getName();
        }
        instructionString += "\n";
    }

}

std::string codeGen::TerminatorInstruction::toString() {
    return instructionString;
}