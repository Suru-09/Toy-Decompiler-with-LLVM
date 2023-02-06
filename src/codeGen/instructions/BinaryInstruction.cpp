#include "codeGen/instructions/BinaryInstruction.h"
#include "utils/CodeGenUtils.h"

#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include "llvm/IR/InstrTypes.h"

codeGen::BinaryInstruction::BinaryInstruction(llvm::Instruction& inst, int numSpaces) {
    logger->info("BinaryInstruction::BinaryInstruction");
    if(llvm::BinaryOperator* binOp = llvm::dyn_cast<llvm::BinaryOperator>(&inst))
    {
        bool first = true;
        logger->error("Number of operands: {}", binOp->getNumOperands());
        for (auto& operand : binOp->operands()) {
            logger->error("Operand: {}", operand->getName().str());
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

            instructionString += binOp->getOpcodeName();
            instructionString += " ";
            first = false;
        }
    }
    else
    {
        logger->error("Cast to BinaryOperator failed");
    }

    if(instructionString.empty())
    {
        logger->error("Instruction string is empty");
    }
    else
    {
        logger->error("Instruction string: {}", instructionString);
    }
}

std::string codeGen::BinaryInstruction::toString() {
    return instructionString;
}