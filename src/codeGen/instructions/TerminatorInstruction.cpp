#include "codeGen/instructions/TerminatorInstruction.h"

codeGen::TerminatorInstruction::TerminatorInstruction(llvm::Instruction& inst) {
    logger->info("TerminatorInstruction::TerminatorInstruction");
}

std::string codeGen::TerminatorInstruction::toString() {
    logger->info("TerminatorInstruction::toString");
    return "";
}