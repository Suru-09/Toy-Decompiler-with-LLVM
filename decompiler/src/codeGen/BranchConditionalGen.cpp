#include "codeGen/BranchConditionalGen.h"
#include "utils/CodeGenUtils.h"

#include <llvm/ADT/PostOrderIterator.h>
#include <llvm/IR/CFG.h>

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

bool codeGen::BranchConditionalGen::shouldTerminatorBeExpanded(const llvm::BasicBlock *bb) {
    return utils::CodeGenUtils::doesInstructionHaveSingleUse(bb->getTerminator());
}

