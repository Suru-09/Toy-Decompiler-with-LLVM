#include "codeGen/GenerateFnBody.h"

#include "logger/LoggerManager.h"
#include "utils/CodeGenUtils.h"
#include "codeGen/instructions/Instruction.h"
#include "codeGen/InstructionInfoRepo.h"
#include "codeGen/InstructionInfo.h"
#include "codeGen/LoopGen.h"
#include "codeGen/BranchConditionalGen.h"
#include "codeGen/InstructionExpander.h"

#include "llvm/Analysis/PostDominators.h"
#include <llvm/ADT/DepthFirstIterator.h>
#include "llvm/IR/Function.h"
#include "llvm/ADT/GraphTraits.h"
#include "llvm/ADT/PostOrderIterator.h"
#include <llvm/IR/Instructions.h>

#include <stack>
#include <vector>

codeGen::GenerateFnBody::GenerateFnBody(llvm::Function& function, const udm::FuncInfo funcInfo) 
: fn(function),
funcInfo(funcInfo)
{
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}

void codeGen::GenerateFnBody::populateInstructionInfoRepoForBasicBlock(
    codeGen::InstructionInfoRepo& repo, llvm::BasicBlock* bb
    , int64_t numSpaces, codeGen::InstructionInfo& instrInfo
)
{
    for(auto& inst: *bb)
    {
        if(inst.getOpcode() != llvm::Instruction::Store)
        {
            continue;
        }

        auto storeInstr = llvm::dyn_cast<llvm::StoreInst>(&inst);
        logger->error("[populateInstructionInfoRepoForBasicBlock] waterducc");
        if(storeInstr)
        {
            auto value = storeInstr->getPointerOperand()->getName().str();
            logger->error("[populateInstructionInfoRepoForBasicBlock] Name added: {}", value);
            instrInfo.setName(value);
        }
        
        instrInfo.setIndentLevel(numSpaces);
        auto storeInst = llvm::dyn_cast<llvm::StoreInst>(&inst);
        std::string value;
        std::string pointer;
        if(storeInst)
        {
            logger->error("[populateInstructionInfoRepoForBasicBlock] storeInst: {}", storeInst->getPointerOperand()->getName().str());
            value = storeInst->getValueOperand()->getName().str();
            pointer = storeInst->getPointerOperand()->getName().str();
        }

        if(value.empty())
        {
            value = inst.getName().str();
        }

        if(pointer.empty())
        {
            pointer = inst.getName().str();
        }

        auto instruction = codeGen::Instruction::getInstruction(inst, numSpaces);
        if(instruction)
        {
            if(expandedInstructions.find({bb->getName().str(), value}) != expandedInstructions.end())
            {
                auto expandedInst = expandedInstructions[{bb->getName().str(), value}];
                instrInfo.setValue(expandedInst);
            }
            else
            {
                instrInfo.setValue(instruction->toString());
            }
        }
        

        repo.insert(instrInfo);
        instrInfo.clear();
    }
}

std::string codeGen::GenerateFnBody::getLoopCondition(llvm::BasicBlock* bb, int64_t numSpaces)
{
    std::string loopCondition = "";
    auto instruction = codeGen::Instruction::getInstruction(bb->back(), numSpaces);
    if(instruction)
    {
        loopCondition = instruction->toString();
        if(expandedInstructions.find({bb->getName().str(), loopCondition}) != expandedInstructions.end())
        {
            std::string expanded = expandedInstructions[{bb->getName().str(), bb->back().getName().str()}];
            if(!expanded.empty())
            {
                loopCondition = expanded;
            }
        }
        logger->error("[getLoopCondition] instruction: {}", loopCondition);
    }
    return loopCondition;
}

bool codeGen::GenerateFnBody::isLoop(const udm::BBInfo& bbinfo)
{
    return bbinfo.getLoopType() != udm::BBInfo::LoopType::NONE;
}

bool codeGen::GenerateFnBody::isConditionalBranch(const udm::BBInfo& bbinfo)
{
    return !isLoop(bbinfo) && !bbinfo.getFollowNode().empty();
}

bool codeGen::GenerateFnBody::isLoopSelfContained(const udm::BBInfo& bbInfo, llvm::BasicBlock* bb)
{
    bool condition = false;
    if(!isLoop(bbInfo))
    {
        return false;
    }
    auto terminator = bb->getTerminator();
    if(terminator)
    {
        auto branchInst = llvm::dyn_cast<llvm::BranchInst>(terminator);
        if(branchInst)
        {
            if(branchInst->isConditional())
            {
                auto value = branchInst->getCondition()->getName().str();
                if (value == bb->getName().str())
                {
                    condition = true;
                }
            }
            else
            {
                return false;
            }
        }
    }
    return condition;
}

std::string codeGen::GenerateFnBody::getSecondBranchOfBrInst(llvm::BasicBlock* bb)
{
    std::string secondBranch = "";
    auto terminator = bb->getTerminator();
    if(terminator)
    {
        auto branchInst = llvm::dyn_cast<llvm::BranchInst>(terminator);
        if(branchInst)
        {
            if(branchInst->isConditional())
            {
                secondBranch = branchInst->getSuccessor(1)->getName().str();
            }
            else
            {
                secondBranch = branchInst->getSuccessor(0)->getName().str();
            }
        }
    }
    return secondBranch;
}

void codeGen::GenerateFnBody::populateInstructionInfoRepo(codeGen::InstructionInfoRepo& repo)
{
    int64_t numSpaces = 4, numSpacesForBlock = 4;
    std::vector<std::string> closingBraces;
    std::vector<std::string> visited;
    
    for(auto it = df_begin(&fn); it != df_end(&fn); ++it)
    {
        auto bb = *it;
        auto bbInfo = funcInfo.getBBInfo(bb->getName().str());
        
        logger->error("[populateInstructionInfoRepo] bb: {}", bb->getName().str());
        logger->error("[populateInstructionInfoRepo] bbInfo: {}", bbInfo.toString());

        codeGen::InstructionInfo instrInfo;

        if(isLoop(bbInfo) || isConditionalBranch(bbInfo))
        {
            std::string loopCondition = getLoopCondition(bb, numSpaces);
            logger->error("[populateInstructionInfoRepo] wtf {}", loopCondition);
            instrInfo.setLoopIfCondition(loopCondition);
        }

        auto foundBB = [&](llvm::BasicBlock* bb) -> std::string
        {
            std::string result = "";
            for(const auto& v: visited)
            {
                if(std::find(closingBraces.begin(), closingBraces.end(), v) != closingBraces.end())
                {
                    result = v;
                    break;
                }
            }
            if(std::find(closingBraces.begin(), closingBraces.end(), bb->getName().str()) != closingBraces.end())
            {
                result = bb->getName().str();
            }
            return  result;
        };

        while(!foundBB(bb).empty())
        {
            logger->error("[populateInstructionInfoRepo] Deleting {} from closingBraces", bb->getName().str());
            numSpaces -= numSpacesForBlock;
            instrInfo.setCloseBraces(true);
            closingBraces.erase(std::find(closingBraces.begin(), closingBraces.end(), foundBB(bb)));
        }
        visited.push_back(bb->getName().str());

        if(isLoopSelfContained(bbInfo, bb))
        {
            logger->error("[populateInstructionInfoRepo] is loop self contained");
            instrInfo.setIndentLevel(numSpaces);
            numSpaces += numSpacesForBlock;
            instrInfo.setLoopType(bbInfo.getLoopType());
            logger->error("[populateInstructionInfoRepo] Second Branch: {} for: {}", getSecondBranchOfBrInst(bb), bb->getName().str());
            closingBraces.push_back(getSecondBranchOfBrInst(bb));
        }

        if(!isLoop(bbInfo) && !isConditionalBranch(bbInfo))
        {
            populateInstructionInfoRepoForBasicBlock(repo, bb, numSpaces, instrInfo);
        }
        

        if(isLoop(bbInfo) && !isLoopSelfContained(bbInfo, bb))
        {
            logger->error("[populateInstructionInfoRepo] is loop ");
            instrInfo.setIndentLevel(numSpaces);
            numSpaces += numSpacesForBlock;
            instrInfo.setLoopType(bbInfo.getLoopType());
            logger->error("[populateInstructionInfoRepo] Second Branch: {} for: {}", getSecondBranchOfBrInst(bb), bb->getName().str());
            closingBraces.push_back(getSecondBranchOfBrInst(bb));
        }

        if(isConditionalBranch(bbInfo))
        {
            logger->error("[populateInstructionInfoRepo] is conditional");
            instrInfo.setIndentLevel(numSpaces);
            numSpaces += numSpacesForBlock;
            instrInfo.setLoopType(bbInfo.getLoopType());
            logger->error("[populateInstructionInfoRepo] Second Branch: {} for: {}", getSecondBranchOfBrInst(bb), bb->getName().str());
            closingBraces.push_back(getSecondBranchOfBrInst(bb));
        }

        if (bb->back().getOpcode() == llvm::Instruction::Ret)
        {
            continue;
        }

        logger->info("[populateInstructionInfoRepo] InstructionInfo loop condition: {}", instrInfo.getLoopIfCondition());
        if(!instrInfo.getLoopIfCondition().empty())
        {
            repo.insert(instrInfo);
        }
        instrInfo.clear();
    }
}

std::string codeGen::GenerateFnBody::generate()
{
    codeGen::InstructionExpander instructionExpander(&fn);
    expandedInstructions = instructionExpander.getExpandedInstructions();

    for(const auto& [key, value]: expandedInstructions)
    {
        logger->error("[generate] expandedInstructions: [{}, {}] -> {}", key.first, key.second, value);
    }

    std::string fnBody  = "";
    codeGen::InstructionInfoRepo instructionInfoRepo{};

    populateInstructionInfoRepo(instructionInfoRepo);
    logger->info("Instruction Info Repo: {}", instructionInfoRepo.toString());

    bool wasIfOrLoop = false;
    for(auto instrInfo: instructionInfoRepo)
    {
        bool copyWas = wasIfOrLoop;

        if(wasIfOrLoop && !instrInfo.isLoop() && !instrInfo.isIf())
        {
            fnBody += utils::CodeGenUtils::getSpaces(instrInfo.getIndentLevel());
            fnBody += instrInfo.getName();
            fnBody += " = ";
            fnBody += instrInfo.getValue();
            fnBody += "\n";
            wasIfOrLoop = false;
        }

        if(instrInfo.getCloseBraces())
        {
            fnBody += utils::CodeGenUtils::getSpaces(instrInfo.getIndentLevel());
            fnBody += "}\n";
            if(instrInfo.getShouldWriteElse())
            {
                fnBody += utils::CodeGenUtils::getSpaces(instrInfo.getIndentLevel());
                fnBody += " else\n";
                fnBody += utils::CodeGenUtils::getSpaces(instrInfo.getIndentLevel());
                fnBody += "{\n";
            }
        }
        
        if(instrInfo.isLoop())
        {
            auto condition = instrInfo.getLoopIfCondition();
            auto indentLevel = instrInfo.getIndentLevel();
            auto loopType = instrInfo.getLoopType();
            fnBody += codeGen::LoopGen::generateLoop(condition, indentLevel, loopType);
            wasIfOrLoop = true;
            continue;
        }

        if(instrInfo.isIf())
        {
            auto condition = instrInfo.getLoopIfCondition();
            auto indentLevel = instrInfo.getIndentLevel();
            fnBody += codeGen::BranchConditionalGen::generateConditional(condition, indentLevel);
            wasIfOrLoop = true;
            continue;
        }

        // if(instrInfo.getName().empty() && instrInfo.getValue().empty())
        // {
        //     continue;
        // }

        if(copyWas == wasIfOrLoop)
        {
            fnBody += utils::CodeGenUtils::getSpaces(instrInfo.getIndentLevel());
            fnBody += instrInfo.getName();
            fnBody += " = ";
            fnBody += instrInfo.getValue();
            fnBody += "\n";
        }
    }

    // print last block
    fnBody += getLastBlock();

    return fnBody;
}

std::string codeGen::GenerateFnBody::getLastBlock()
{
    std::string fnBody = "";
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