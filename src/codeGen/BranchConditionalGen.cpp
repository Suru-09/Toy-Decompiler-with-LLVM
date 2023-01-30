#include "codeGen/BranchConditionalGen.h"
#include "utils/CodeGenUtils.h"

std::string codeGen::BranchConditionalGen::generateConditional(std::shared_ptr<Instruction> instr, int numSpaces, bool isElseIf)
{
   std::string result = utils::CodeGenUtils::generateSpaces(numSpaces);
   std::string condition = instr->toString();
   
   if(isElseIf)
   {
      result += "else if(" + condition + ")\n";
   }
   else
   {
      result += "if(" + condition + ")\n";
   }

   return result;
}