#include "codeGen/instructions/BinaryInstruction.h"
#include "codeGen/TranslateOperator.h"
#include "utils/CodeGenUtils.h"

#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include "llvm/IR/InstrTypes.h"

codeGen::BinaryInstruction::BinaryInstruction(llvm::Instruction& inst, int numSpaces) {
    logger->info("BinaryInstruction::BinaryInstruction");
    bool printLhs = utils::CodeGenUtils::canAssignTo(&inst);
    if(printLhs)
    {
        instructionString += inst.getName().str() + " = ";
    }

    if(auto* binOp = llvm::dyn_cast<llvm::BinaryOperator>(&inst))
    {
        bool first = true;
        logger->info("[BinaryInstruction::BinaryInstruction] Number of operands: {}", binOp->getNumOperands());
        for (auto& operand : binOp->operands()) {
            logger->info("[BinaryInstruction::BinaryInstruction] Operand: {}", operand->getName().str());
            instructionString += utils::CodeGenUtils::llvmValueToString(operand) + " ";

            if(!first)
            {
                continue;
            }

            // +, -, *, etc.
            std::string predicate = binOp->getOpcodeName();
            instructionString += codeGen::TranslateOperator::translateOperator(predicate) + " ";
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