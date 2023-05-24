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
               bool isArgumentToFunction = false;
               std::string savedArgument;
                for(auto& labelAndValue: labelsAndValues)
                {
                     std::string rhsLocalVar = labelAndValue.second;
                     std::string basicBlockName = labelAndValue.first;

                     if(!isArgumentToFunction)
                     {
                        isArgumentToFunction = utils::CodeGenUtils::isInstructionAnArgumentToTheLLVMFunction(m_llvmFun, rhsLocalVar);
                        savedArgument = rhsLocalVar;
                     }

                     aliases.emplace_back(basicBlockName, rhsLocalVar, lhsStackVarName);
                     logger->info("[PHINodeHandler::getPHINodeAliases] Found alias: value: <{}> for stack_var: <{}> in basic block: {}", rhsLocalVar, lhsStackVarName, basicBlockName);
                }

                // if we saved an we replace the stack variable name with the argument name
                std::vector<StackVarAlias> newAliases;
               std::for_each(aliases.begin(), aliases.end(), [&savedArgument, &inst, &newAliases](StackVarAlias& alias){
                   if(alias.getStackVarName() == inst.getName().str() && !savedArgument.empty())
                   {
                       newAliases.emplace_back("global", savedArgument, alias.getLocalVar());
                       alias.setLocalVar(savedArgument);
                   }
               });

                aliases.insert(aliases.end(), newAliases.begin(), newAliases.end());
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

         std::string value = utils::CodeGenUtils::llvmValueToString(incomingValue);
         std::string label = incomingBlock->getName().str();
         labelsAndValues.emplace_back(label, value);
    }
    return labelsAndValues;
}

