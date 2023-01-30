#include "codeGen/instructions/BinaryInstruction.h"


codeGen::BinaryInstruction::BinaryInstruction(llvm::Instruction& inst) {
    logger->info("BinaryInstruction::BinaryInstruction");
}

std::string codeGen::BinaryInstruction::toString() {
    logger->info("BinaryInstruction::toString");
    return "";
}