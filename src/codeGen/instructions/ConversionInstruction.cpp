#include "codeGen/instructions/ConversionInstruction.h"

codeGen::ConversionInstruction::ConversionInstruction(llvm::Instruction& inst) {
    logger->info("ConversionInstruction::ConversionInstruction");
}

std::string codeGen::ConversionInstruction::toString() {
    logger->info("ConversionInstruction::toString");
    return "";
}