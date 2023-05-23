#include "codeGen/DefineVariablesHandler.h"

#include "logger/LoggerManager.h"
#include "codeGen/Variable.h"
#include "utils/CodeGenUtils.h"


#include <llvm/IR/CFG.h>
#include <llvm/ADT/PostOrderIterator.h>
#include <llvm/IR/Instructions.h>

codeGen::DefineVariablesHandler::DefineVariablesHandler(const llvm::Function &llvmFn)
: llvmFn(llvmFn)
{
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}

std::map<std::string, std::vector<codeGen::Variable>> codeGen::DefineVariablesHandler::handle() {
    std::map<std::string, std::vector<codeGen::Variable>> variables;

    llvm::ReversePostOrderTraversal<const llvm::Function*> rpot(&llvmFn);
    for(auto bb: rpot)
    {
        auto terminator = bb->getTerminator();
        std::string branchCondition;
        if(auto* branchInstr = llvm::dyn_cast<llvm::BranchInst>(terminator))
        {
            if(branchInstr->isConditional())
            {
                branchCondition = branchInstr->getCondition()->getName().str();
            }
        }

        for(auto& instr: *bb)
        {
            // !!!! --- phi nodes symbolize variables that are saved on the stack,
            // which will later be replaced by the local variables for simplicity.
            // same goes for cast instructions, they are not needed in the decompiled code,
            // creating lots of clutter.
            if(instr.getOpcode() == llvm::Instruction::PHI || instr.getName().empty() || instr.isCast())
            {
                continue;
            }

            // check if variable has single use && is it only used in branch condition
            // this was added once I made the decision not to print if and while loops
            // conditions as separate variables, instead I print them directly in the
            // if and while loops headers.
            if(utils::CodeGenUtils::doesInstructionHaveSingleUse(&instr) && branchCondition == instr.getName().str())
            {
                continue;
            }

            // check if variable has single use && it is used in a select instruction
            // makes reading easier if the condition does not have a separate variable
            if(utils::CodeGenUtils::isInstructionUsedInTernaryOperatorAndHasSingleUse(&instr))
            {
                continue;
            }

            // get variable type
            logger->debug("[DefineVariablesHandler::handle] Variable name added for definition: {}", instr.getName().str());
            auto type = utils::CodeGenUtils::typeToString(instr.getType());
            auto initialValue = "0";
            Variable var = Variable(instr.getName().str(), type, initialValue);
            if(variables.find(bb->getName().str()) != variables.end())
            {
                // if a variable already exists in the block, then push at the end of the vector.
                variables[bb->getName().str()].push_back(var);
                continue;
            }
            // if a variable does not exist in the block, then create a new vector and insert it into the map.
            variables.insert_or_assign(bb->getName().str(), std::vector<Variable>{var});
        }
    }
    return variables;
}



bool codeGen::DefineVariablesHandler::checkIfBBIsFirstOfHasNoIntructions(const llvm::BasicBlock &bb) {
    bool isFirst = false, hasNoInstructions = false;
    if(bb.getSinglePredecessor() == nullptr)
    {
        isFirst = true;
    }
    std::size_t instrCount = 0;
    for(auto& instr: bb)
    {
        if(!instr.isTerminator())
        {
            ++instrCount;
        }
    }
    instrCount == 0 ? hasNoInstructions = true : hasNoInstructions = false;
    return isFirst || hasNoInstructions;
}

std::string codeGen::DefineVariablesHandler::getFirstBBFromVector(const std::vector<std::string> &bbs) {
    llvm::ReversePostOrderTraversal<const llvm::Function*> rpot(&llvmFn);
    if(bbs.empty())
    {
        return "";
    }
    for(auto bb: rpot)
    {
        auto found = std::find(bbs.begin(), bbs.end(), bb->getName().str());
        if(found != bbs.end())
        {
            return bb->getName().str();
        }
    }

    return bbs.front();
}

std::vector<std::string> codeGen::DefineVariablesHandler::constructBBsVector(const llvm::PHINode* phiNode) {
    std::vector<std::string> bbs;
    for(std::size_t i = 0; i < phiNode->getNumIncomingValues(); ++i)
    {
        auto incoming = phiNode->getIncomingBlock(i);
        bbs.push_back(incoming->getName().str());
    }
    return bbs;
}
