#include "codeGen/instructions/BinaryInstruction.h"

#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include "llvm/IR/InstrTypes.h"

codeGen::BinaryInstruction::BinaryInstruction(llvm::Instruction& inst) {
    logger->info("BinaryInstruction::BinaryInstruction");
    if(llvm::BinaryOperator* binOp = llvm::dyn_cast<llvm::BinaryOperator>(&inst))
    {
        // auto operatorOne = binOp->getOperand(0);
        // auto operatorTwo = binOp->getOperand(1);
        // auto operatorThree = binOp->getOperand(1);

        // auto operatorOneType = operatorOne->getType();
        // auto operatorTwoType = operatorTwo->getType();
        // auto operatorThreeType = operatorThree->getType();

        // instructionString = operatorOne->getName().str() + " " + binOp->getOpcodeName() + " " 
        //     + operatorTwo->getName().str() + " " + operatorThree->getName().str() + "\n";
        for (auto& operand : binOp->operands()) {
            std::string name = operand->getName().str();
            instructionString += name;
            if(name == "")
            {
                instructionString += operand->getType()->getPrimitiveSizeInBits();
            }
            instructionString += "\n";
        }

    }
}

std::string codeGen::BinaryInstruction::toString() {
    return instructionString;
}