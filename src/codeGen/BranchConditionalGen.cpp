#include "codeGen/BranchConditionalGen.h"
#include "utils/CodeGenUtils.h"

std::string codeGen::BranchConditionalGen::generateConditional(std::shared_ptr<Instruction> instr, int numSpaces, bool isElseIf)
{
   std::string result = utils::CodeGenUtils::getSpaces(numSpaces);
   std::string condition = instr->toString();
   
   if(isElseIf)
   {
      result += "else if(" + condition + ")\n";
   }
   else
   {
      result += "if(" + condition + ")\n";
   }
   result += utils::CodeGenUtils::getSpaces(numSpaces) + "{\n";

   return result;
}