#include "codeGen/ast/PHINodeHandler.h"
#include "logger/LoggerManager.h"
#include "utils/CodeGenUtils.h"


#include <llvm/ADT/PostOrderIterator.h>

codeGen::ast::PHINodeHandler::PHINodeHandler(llvm::Function &llvmFun)
: m_llvmFun(llvmFun)
{
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}

std::vector<codeGen::ast::StackVarAlias> codeGen::ast::PHINodeHandler::getPHINodeAliases() {
    std::vector<StackVarAlias> aliases;
    llvm::ReversePostOrderTraversal<llvm::Function*> RPOT(&m_llvmFun);
    for(auto& bb: RPOT)
    {
        for(auto& inst: *bb)
        {
           if(inst.getOpcode() == llvm::Instruction::PHI)
           {
               auto* phiPtr = llvm::dyn_cast<llvm::PHINode>(&inst);
               if(!phiPtr)
               {
                   logger->error("[PHINodeHandler::getPHINodeAliases] Failed to cast instruction to PHINode, something is wrong...");
                   continue;
               }

               std::string lhsStackVarName = phiPtr->getName().str();
               std::vector<std::pair<std::string, std::string>> labelsAndValues = getLabelsAndValueFromPhiNode(phiPtr);
                for(auto& labelAndValue: labelsAndValues)
                {
                     std::string rhsLocalVar = labelAndValue.second;
                     std::string basicBlockName = bb->getName().str();
                     aliases.emplace_back(basicBlockName, rhsLocalVar, lhsStackVarName);
                     logger->info("[PHINodeHandler::getPHINodeAliases] Found alias: lvar: <{}> for stack_var: <{}> in basic block: {}", rhsLocalVar, lhsStackVarName, basicBlockName);
                }
           }
        }
    }
    return aliases;
}

std::vector<std::pair<std::string, std::string>> codeGen::ast::PHINodeHandler::getLabelsAndValueFromPhiNode(
        llvm::PHINode *phiNode)
{
    std::vector<std::pair<std::string, std::string>> labelsAndValues;
    for(std::size_t i = 0; i < phiNode->getNumIncomingValues(); ++i)
    {
         auto* incomingBlock = phiNode->getIncomingBlock(i);
         auto* incomingValue = phiNode->getIncomingValue(i);
         std::string value;
         if(auto* instruction = llvm::dyn_cast<llvm::Instruction>(incomingValue))
         {
             value = instruction->getName().str();
             std::string label = incomingBlock->getName().str();
             labelsAndValues.emplace_back(label, value);
         }
         else {
            value = utils::CodeGenUtils::llvmValueToString(incomingValue);
             std::string label = incomingBlock->getName().str();
             labelsAndValues.emplace_back(label, value);
         }
    }
    return labelsAndValues;
}

