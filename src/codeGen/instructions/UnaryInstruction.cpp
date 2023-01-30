#include "codeGen/instructions/UnaryInstruction.h"

codeGen::UnaryInstruction::UnaryInstruction(llvm::Instruction& inst) {
    logger->info("UnaryInstruction::UnaryInstruction");
}

std::string codeGen::UnaryInstruction::toString() {
    logger->info("UnaryInstruction::toString");
    return "";
}