#include "codeGen/instructions/OtherInstruction.h"

codeGen::OtherInstruction::OtherInstruction(llvm::Instruction& inst) {
    logger->info("OtherInstruction::OtherInstruction");
}

std::string codeGen::OtherInstruction::toString() {
    logger->info("OtherInstruction::toString");
    return "";
}