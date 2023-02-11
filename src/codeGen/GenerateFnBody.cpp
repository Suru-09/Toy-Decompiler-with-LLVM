#include "codeGen/GenerateFnBody.h"

#include "logger/LoggerManager.h"
#include "utils/CodeGenUtils.h"
#include "codeGen/instructions/Instruction.h"
#include "codeGen/InstructionInfoRepo.h"
#include "codeGen/InstructionInfo.h"
#include "codeGen/LoopGen.h"
#include "codeGen/BranchConditionalGen.h"

#include "llvm/Analysis/PostDominators.h"
#include <llvm/ADT/DepthFirstIterator.h>
#include "llvm/IR/Function.h"
#include "llvm/ADT/GraphTraits.h"
#include "llvm/ADT/PostOrderIterator.h"

#include <vector>

codeGen::GenerateFnBody::GenerateFnBody(llvm::Function& function, const udm::FuncInfo funcInfo) 
: fn(function),
funcInfo(funcInfo)
{
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}

bool codeGen::GenerateFnBody::isBBSuccesorOf(llvm::BasicBlock* bb, llvm::BasicBlock* succBB)
{
    for(auto succ: llvm::successors(bb))
    {
        if(succ->getName().str() == succBB->getName().str())
        {
            return true;
        }
    }
    return false;
}

bool codeGen::GenerateFnBody::isBBPredecessorOf(llvm::BasicBlock* bb, llvm::BasicBlock* predBB)
{
    for(auto pred: llvm::predecessors(bb))
    {
        if(pred->getName().str() == predBB->getName().str())
        {
            return true;
        }
    }
    return false;
}

void codeGen::GenerateFnBody::dfsForClosingBrackets(
    std::set<std::string>& visited,
    llvm::BasicBlock* bb,
    std::map<std::string, uint64_t>& closingBrackets
)
{
    // iterate over function using depth first search without LLVM iterators
    visited.insert(bb->getName().str());

    for(auto succ: llvm::successors(bb))
    {
        if(visited.find(succ->getName().str()) == visited.end())
        {
            dfsForClosingBrackets(visited, succ, closingBrackets);
            closingBrackets[bb->getName().str()] = 1;
        }
    }
}

void codeGen::GenerateFnBody::populateInstructionInfoRepo(codeGen::InstructionInfoRepo& repo)
{
    int64_t numSpaces = 4, numSpacesForBlock = 4;
    llvm::ReversePostOrderTraversal<llvm::Function*> rpot(&fn);

    std::set<std::string> visited;
    std::map<std::string, uint64_t> closingBrackets;
    llvm::BasicBlock* entryBB = &fn.getEntryBlock();
    dfsForClosingBrackets(visited, entryBB, closingBrackets);

    for(const auto& [key, value]: closingBrackets)
    {
        logger->error("[populateInstructionInfoRepo] closingBrackets: {} {}", key, value);
    }

    for(auto it = df_begin(&fn); it != df_end(&fn); ++it)
    {
       auto bb = *it;
       auto bbInfo = funcInfo.getBBInfo(bb->getName().str());
       logger->error("[populateInstructionInfoRepo] bb: {}", bb->getName().str());
       
        if(closingBrackets.find(bb->getName().str()) != closingBrackets.end())
        {
            logger->error("[populateInstructionInfoRepo] closing bracket");
            if(numSpaces - numSpacesForBlock >= numSpacesForBlock)
            {
                numSpaces -= numSpacesForBlock;
            }
        }

        if (bb->back().getOpcode() == llvm::Instruction::Ret)
        {
            continue;
        }

       logger->error("[populateInstructionInfoRepo] bb: {}", bb->getName().str());
       logger->error("[populateInstructionInfoRepo] bbInfo: {}", bbInfo.toString());
       codeGen::InstructionInfo instrInfo;

       
        for(auto& inst: *bb)
        {
            if(inst.getOpcode() == llvm::Instruction::Br ||  inst.getOpcode() == llvm::Instruction::Ret)
            {
                continue;
            }

            if(inst.hasName())
            {
                instrInfo.setName(inst.getName().str());
            }
            instrInfo.setIndentLevel(numSpaces);

            auto instruction = codeGen::Instruction::getInstruction(inst, numSpaces);
            if(instruction)
            {
                instrInfo.setValue(instruction->toString());
            }

            repo.insert(instrInfo);
            instrInfo.clear();
        }

        auto instruction = codeGen::Instruction::getInstruction(bb->back(), numSpaces);
        if(instruction)
        {
            logger->error("[populateInstructionInfoRepo] instruction: {}", instruction->toString());
            auto str = instruction->toString();
            instrInfo.setLoopIfCondition(str);
        }
        else {
            continue;
        }

        if(bbInfo.getLoopType() != udm::BBInfo::LoopType::NONE)
        {
            logger->error("[populateInstructionInfoRepo] is loop ");
            instrInfo.setIndentLevel(numSpaces);
            numSpaces += numSpacesForBlock;
            instrInfo.setLoopType(bbInfo.getLoopType());
            repo.insert(instrInfo);
            instrInfo.clear();
        }
        else if(!bbInfo.getFollowNode().empty() && bbInfo.getLoopType() == udm::BBInfo::LoopType::NONE)
        {
            logger->error("[populateInstructionInfoRepo] is conditional");
            instrInfo.setIndentLevel(numSpaces);
            numSpaces += numSpacesForBlock;
            instrInfo.setLoopType(bbInfo.getLoopType());
            repo.insert(instrInfo);
            instrInfo.clear();
        }
    }
}

std::string codeGen::GenerateFnBody::generate()
{
    std::string fnBody  = "";
    codeGen::InstructionInfoRepo instructionInfoRepo{};

    populateInstructionInfoRepo(instructionInfoRepo);
    logger->info("Instruction Info Repo: {}", instructionInfoRepo.toString());

    int64_t currIndentLevel = -1;
    for(auto instrInfo: instructionInfoRepo)
    {
        if(currIndentLevel == -1)
        {
            currIndentLevel = instrInfo.getIndentLevel();
        }
        else if(currIndentLevel < instrInfo.getIndentLevel())
        {
            currIndentLevel = instrInfo.getIndentLevel();
        }

        int64_t index = 4;
        while(currIndentLevel - index >= instrInfo.getIndentLevel())
        {
            fnBody += utils::CodeGenUtils::getSpaces(currIndentLevel - index);
            fnBody += "}\n";
            index += 4;
        }
        
        if(instrInfo.isLoop())
        {
            auto condition = instrInfo.getLoopIfCondition();
            auto indentLevel = instrInfo.getIndentLevel();
            auto loopType = instrInfo.getLoopType();
            fnBody += codeGen::LoopGen::generateLoop(condition, indentLevel, loopType);
            continue;
        }

        if(instrInfo.isIf())
        {
            auto condition = instrInfo.getLoopIfCondition();
            auto indentLevel = instrInfo.getIndentLevel();
            fnBody += codeGen::BranchConditionalGen::generateConditional(condition, indentLevel);
            continue;
        }

        fnBody += utils::CodeGenUtils::getSpaces(instrInfo.getIndentLevel());
        if(!instrInfo.getName().empty())
        {
            fnBody += instrInfo.getName();
            fnBody += " = ";
        }
        fnBody += instrInfo.getValue();
        fnBody += "\n";
    }

    while(currIndentLevel > 0)
    {
        fnBody += utils::CodeGenUtils::getSpaces(currIndentLevel);
        fnBody += "}\n";
        currIndentLevel -= 4;
    }

    // print last block
    for(auto& inst: fn.back())
    {
        auto instruction = codeGen::Instruction::getInstruction(inst, 4);
        if(instruction)
        {
            if(inst.hasName())
            {
                fnBody += utils::CodeGenUtils::getSpaces(4);
                fnBody += inst.getName().str();
                fnBody += " = ";
            }
            fnBody += instruction->toString();
            fnBody += "\n";
        }
    }
    fnBody += "}\n";

    return fnBody;
}