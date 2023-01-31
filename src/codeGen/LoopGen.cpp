#include "codeGen/LoopGen.h"
#include "utils/CodeGenUtils.h"

#include <iostream>
#include <memory>

std::string codeGen::LoopGen::generateLoop(std::shared_ptr<Instruction> instr, int numSpaces, udm::BBInfo::LoopType loopType)
{
   std::string result = utils::CodeGenUtils::getSpaces(numSpaces);
   std::string condition = instr->toString();
   
    if(loopType == udm::BBInfo::LoopType::WHILE)
    {
        result += "while(" + condition + ")\n";
    }
    else if(loopType == udm::BBInfo::LoopType::DO_WHILE)
    {
        result += "do\n";
    }
    result += utils::CodeGenUtils::getSpaces(numSpaces) + "{\n";

    return result;
}