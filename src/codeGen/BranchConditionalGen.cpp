#include "codeGen/BranchConditionalGen.h"


std::string codeGen::BranchConditionalGen::generateConditional(std::shared_ptr<Instruction> instr, bool isElseIf)
{
   std::string result = "";
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