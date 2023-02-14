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

std::vector<codeGen::ExpandedInstr> codeGen::InstructionExpander::getExpandedInstructions()
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

    // auto storeInst = llvm::dyn_cast<llvm::StoreInst>(inst);
    // llvm::Value* valueOperand = storeInst ? storeInst->getValueOperand() : nullptr;
    // if(inst->getOpcode() == llvm::Instruction::Store && valueOperand && valueOperand->getName().str().empty())
    // {
    //     logger->error("[expandInstruction] Store expanded: {}", expandedInst);
    //     return expandedInst;
    // }

    for (auto &op : inst->operands()) {
        std::string opName = op->hasName() ? op->getName().str() : "";
        std::string parentStr = inst->getParent()->getName().str();
        if (opName.empty()) {
            continue;
        }

        codeGen::ExpandedInstr searchedInstr(parentStr, opName);
        auto found = std::find(expandedInstructions.rbegin(), expandedInstructions.rend(), searchedInstr);
        if(found == expandedInstructions.rend())
        {
            logger->error("[expandInstruction] Operand [{}, {}] not found in expanded instructions", parentStr, opName);
            continue;
        }

        std::string opValue = found->getExpandedInstr();
        logger->error("[expandInstruction] Opvalue: [{}] vs: expandedInst: [{}]", opValue, expandedInst);
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
            if(!inst.hasName())
            {
                continue;
            }
            // if(llvm::StoreInst* storeInst = llvm::dyn_cast<llvm::StoreInst>(&inst))
            // {
            //     instName = storeInst->getPointerOperand()->getName().str();
            // }
            codeGen::ExpandedInstr searchedInstr(bbName, instName);
            std::string expandedInst = expandInstruction(&inst, 0);
            searchedInstr.setExpandedInstr(expandedInst);

            expandedInstructions.push_back(searchedInstr);
        }
    }
}