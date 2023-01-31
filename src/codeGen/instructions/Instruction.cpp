#include "codeGen/instructions/Instruction.h"

#include "codeGen/instructions/OtherInstruction.h"
#include "codeGen/instructions/TerminatorInstruction.h"
#include "codeGen/instructions/BinaryInstruction.h"
#include "codeGen/instructions/UnaryInstruction.h"
#include "codeGen/instructions/ConversionInstruction.h"
#include "codeGen/instructions/BitwiseBinaryInstruction.h"

#include "logger/LoggerManager.h"

std::shared_ptr<codeGen::Instruction> codeGen::Instruction::getInstruction(llvm::Instruction& inst, int numSpaces) {
    if(inst.isTerminator()) 
    {
        return std::make_shared<codeGen::TerminatorInstruction>(inst);
    }
    else if(inst.isBinaryOp()) 
    {
        return std::make_shared<codeGen::BinaryInstruction>(inst, numSpaces);
    }
    else if(inst.isUnaryOp()) 
    {
        return std::make_shared<codeGen::UnaryInstruction>(inst);
    }
    else if(inst.isCast()) 
    {
        return std::make_shared<codeGen::ConversionInstruction>(inst, numSpaces);
    }
    else if(inst.isBitwiseLogicOp()) 
    {
        return std::make_shared<codeGen::BitwiseBinaryInstruction>(inst, numSpaces);
    }
    else 
    {
        return std::make_shared<codeGen::OtherInstruction>(inst, numSpaces);
    }
}

codeGen::Instruction::Instruction() {
    instructionString = "";
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}