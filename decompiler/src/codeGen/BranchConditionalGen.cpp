#include "codeGen/BranchConditionalGen.h"
#include "utils/CodeGenUtils.h"

std::string codeGen::BranchConditionalGen::generateConditional(const std::string& condition, int numSpaces, bool isElseIf)
{
   std::string result = utils::CodeGenUtils::getSpaces(numSpaces);
   
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