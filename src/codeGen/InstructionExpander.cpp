#include "codeGen/InstructionExpander.h"

#include "codeGen/instructions/Instruction.h"
#include "logger/LoggerManager.h"   

#include <llvm/ADT/PostOrderIterator.h>
#include <llvm/Analysis/PostDominators.h>
#include <llvm/IR/Instructions.h>

codeGen::InstructionExpander::InstructionExpander(llvm::Function *f) 
:  fn(*f)
{
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
    initExpandedInstructions();
}

std::map<std::pair<std::string, std::string>, std::string> codeGen::InstructionExpander::getExpandedInstructions()
{
    return expandedInstructions;
}

std::string codeGen::InstructionExpander::expandInstruction(llvm::Instruction *inst, int64_t offset) {
    logger->error("Expanding instruction: {}", inst->getOpcodeName());
    std::string expandedInst = "";

    auto instrObj = codeGen::Instruction::getInstruction(*inst, offset);
    if (instrObj != nullptr) {
        expandedInst = instrObj->toString();
    }
    else {
        logger->error("[expandInstruction] Instruction not supported: {}", inst->getOpcodeName());
        return "";
    }

    auto storeInst = llvm::dyn_cast<llvm::StoreInst>(inst);
    llvm::Value* valueOperand = storeInst ? storeInst->getValueOperand() : nullptr;
    if(inst->getOpcode() == llvm::Instruction::Store && valueOperand && valueOperand->getName().str().empty())
    {
        logger->error("[expandInstruction] Store expanded: {}", expandedInst);
        return expandedInst;
    }

    for (auto &op : inst->operands()) {
        std::string opName = "";
        opName = op->hasName() ? op->getName().str() : "";
        if (opName.empty()) {
            continue;
        }

        auto parentStr = inst->getParent()->getName().str();
        auto opNameStr = opName;
        auto opKey = std::make_pair(std::move(parentStr), std::move(opNameStr));
        for(auto it = expandedInstructions.rbegin(); it != expandedInstructions.rend(); ++it)
        {
            if(it->first.second == opName)
            {
                opKey.first = it->first.first;
                opKey.second = it->first.second;
                break;
            }
        }

        if(expandedInstructions.find(opKey) == expandedInstructions.end()) {
            logger->error("[expandInstruction] Operand not found in map: {}", opName);
            continue;
        }

        std::string opValue = expandedInstructions[opKey];
        // if operand is used in expanded instruction, replace it with its value
        if(expandedInst.find(opName) != std::string::npos) {
            logger->debug("[expandInstruction] Replacing operand {} with value {}", opName, opValue);
            expandedInst.replace(expandedInst.find(opName), opName.length(), opValue);
        }
    }

    return expandedInst;
}

void codeGen::InstructionExpander::initExpandedInstructions()
{
    llvm::ReversePostOrderTraversal<llvm::Function*> rpot(&fn);
    for (auto &bb : rpot) 
    {
        for (auto &inst : *bb) 
        {
            std::string bbName = bb->getName().str();
            std::string instName = inst.getName().str();
            if(llvm::StoreInst* storeInst = llvm::dyn_cast<llvm::StoreInst>(&inst))
            {
                instName = storeInst->getPointerOperand()->getName().str();
            }
            std::string expandedInst = expandInstruction(&inst, 0);
            expandedInstructions.insert_or_assign(std::make_pair<std::string, std::string>(std::move(bbName), std::move(instName)), std::move(expandedInst));
        }
    }
}