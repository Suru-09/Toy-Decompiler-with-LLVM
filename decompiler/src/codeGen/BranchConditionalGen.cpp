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

std::unordered_map<std::string, std::string>
codeGen::BranchConditionalGen::collectExpansionRequiredTerminatorInstructions(const llvm::Function &func) {
    std::unordered_map<std::string, std::string> expansionRequired;
    llvm::ReversePostOrderTraversal<const llvm::Function*> rpot(&func);
    for(auto bb: rpot) {
        auto terminator = bb->getTerminator();
        if (utils::CodeGenUtils::doesInstructionHaveSingleUse(terminator))
        {
            expansionRequired[terminator->getName().str()] = utils::CodeGenUtils::getInstructionValue(terminator);
        }
    }
    return expansionRequired;
}
