#include "codeGen/instructions/BitwiseBinaryInstruction.h"
#include "utils/CodeGenUtils.h"

#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include "llvm/IR/InstrTypes.h"

codeGen::BitwiseBinaryInstruction::BitwiseBinaryInstruction(llvm::Instruction& inst, int numSpaces) {

    if(llvm::BinaryOperator* bitwiseOp = llvm::dyn_cast<llvm::BinaryOperator>(&inst))
    {
        bool first = true;
        for (auto& operand : bitwiseOp->operands()) {
            std::string name = operand->getName().str();
            instructionString += name + " ";
            
            if(name.empty())
            {
                if(llvm::ConstantInt* constInt = llvm::dyn_cast<llvm::ConstantInt>(operand))
                {
                    instructionString += std::to_string(constInt->getSExtValue());
                }
                else if(llvm::ConstantFP* constFP = llvm::dyn_cast<llvm::ConstantFP>(operand))
                {
                    instructionString += std::to_string(constFP->getValueAPF().convertToDouble());
                }
                else
                {
                    logger->error("Unknown operand type");
                }
            }
            
            if(!first)
            {
                continue;
            }
            
            instructionString += bitwiseOp->getOpcodeName();
            instructionString += " ";
            first = false;
        }
    }
}

std::string codeGen::BitwiseBinaryInstruction::toString() {
    return instructionString;
}