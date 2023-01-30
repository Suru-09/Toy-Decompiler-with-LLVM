#include "codeGen/instructions/BitwiseBinaryInstruction.h"

codeGen::BitwiseBinaryInstruction::BitwiseBinaryInstruction(llvm::Instruction& inst) {
    logger->info("BitwiseBinaryInstruction::BitwiseBinaryInstruction");
}

std::string codeGen::BitwiseBinaryInstruction::toString() {
    logger->info("BitwiseBinaryInstruction::toString");
    return "";
}