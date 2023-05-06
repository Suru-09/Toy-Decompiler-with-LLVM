#include "codeGen/GenerateFnBody.h"

#include "logger/LoggerManager.h"
#include "utils/CodeGenUtils.h"
#include "codeGen/instructions/Instruction.h"
#include "codeGen/InstructionInfoRepo.h"
#include "codeGen/InstructionInfo.h"
#include "codeGen/LoopHandler.h"
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
    , int64_t numSpaces, codeGen::InstructionInfo instrInfo
)
{
    for(auto& inst: *bb)
    {
        instrInfo.clear();
        auto bbInfo = funcInfo.getBBInfo(bb->getName().str());
        if( (isLoop(bbInfo) || isConditionalBranch(bbInfo)) && instrInfo.getCloseBraces() == true)
        {
            instrInfo.setCloseBraces(false);
        }
        
        if(inst.getOpcode() != llvm::Instruction::Store)
        {
            continue;
        }
        logger->error("[populateInstructionInfoRepoForBasicBlock] waterducc : {}", inst.getOpcodeName());

        auto storeInst = llvm::dyn_cast<llvm::StoreInst>(&inst);
        if(storeInst)
        {
            auto value = storeInst->getPointerOperand()->getName().str();
            logger->error("[populateInstructionInfoRepoForBasicBlock] Name added: {}", value);
            instrInfo.setName(value);
        }
        else
        {
            continue;
        }
        
        instrInfo.setIndentLevel(numSpaces);
        std::string value;
        std::string pointer;

        value = storeInst->getValueOperand()->getName().str();
        if(value.empty())
        {
            if (llvm::dyn_cast<llvm::ConstantInt>(storeInst->getValueOperand()) )
            {
                auto constantInt = llvm::dyn_cast<llvm::ConstantInt>(storeInst->getValueOperand());
                value = std::to_string(constantInt->getSExtValue());
            }
            else if (llvm::dyn_cast<llvm::ConstantFP>(storeInst->getValueOperand()) )
            {
                auto constantFP = llvm::dyn_cast<llvm::ConstantFP>(storeInst->getValueOperand());
                value = std::to_string(constantFP->getValueAPF().convertToDouble());
            }
            if(!value.empty())
            {
                logger->error("[populateInstructionInfoRepoForBasicBlock] value: {}", value);
                instrInfo.setValue(value);
                repo.insert(instrInfo);
                continue;
            }
        }

        pointer = storeInst->getPointerOperand()->getName().str();
        logger->error("[populateInstructionInfoRepoForBasicBlock] storeInst: {} -> {}", pointer, value);
        

        auto instruction = codeGen::Instruction::getInstruction(inst, numSpaces);
        if(instruction)
        {
            codeGen::ExpandedInstr expandedInstr{bb->getName().str(), value};
            auto found = std::find(expandedInstructions.rbegin(), expandedInstructions.rend(), expandedInstr);
            if(found != expandedInstructions.rend())
            {
                auto expandedInst = found->getExpandedInstr();
                instrInfo.setValue(expandedInst);
            }
            else
            {
                instrInfo.setValue(instruction->toString());
            }
        }
        
        repo.insert(instrInfo);
    }
}

std::string codeGen::GenerateFnBody::getLoopCondition(llvm::BasicBlock* bb, int64_t numSpaces)
{
    std::string loopCondition = "";
    auto instruction = codeGen::Instruction::getInstruction(bb->back(), numSpaces);
    if(instruction)
    {
        auto terminator = bb->getTerminator();
        std::string search = "";
        loopCondition = instruction->toString();

        if(terminator->getOpcode() == llvm::Instruction::Br)
        {
            auto brInst = llvm::dyn_cast<llvm::BranchInst>(terminator);
            if(brInst->isConditional())
            {
                search = brInst->getCondition()->getName().str();
            }
        }
        codeGen::ExpandedInstr expandedInstr{bb->getName().str(), search};
        auto found = std::find(expandedInstructions.begin(), expandedInstructions.end(), expandedInstr);
        if(found != expandedInstructions.end())
        {
            std::string expanded = found->getExpandedInstr();
            if(!expanded.empty())
            {
                loopCondition = expanded;
            }
        }
        logger->error("[getLoopCondition] instruction: {} for: [{}]", loopCondition, bb->back().getName().str());
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
                auto value = branchInst->getSuccessor(0)->getName().str();
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

    auto isBBConditional = [&](const std::string& bbName) {
        auto bbInfo = funcInfo.getBBInfo(bbName);
        return isConditionalBranch(bbInfo);
    };
    
    llvm::ReversePostOrderTraversal<llvm::Function*> rpot(&fn);
    for(auto it = df_begin(&fn); it != df_end(&fn); ++it)
    {
        auto bb = *it;
        auto bbInfo = funcInfo.getBBInfo(bb->getName().str());
        
        logger->error("[populateInstructionInfoRepo] bb: {}", bb->getName().str());
        logger->error("[populateInstructionInfoRepo] bbInfo: {}", bbInfo.toString());

        codeGen::InstructionInfo instrInfo;
        instrInfo.setIndentLevel(numSpaces);
        instrInfo.setSHouldWriteElse(false);
        instrInfo.setCloseBraces(false);

        if(isLoop(bbInfo) || isConditionalBranch(bbInfo))
        {
            std::string loopCondition = getLoopCondition(bb, numSpaces);
            logger->error("[populateInstructionInfoRepo] wtf {}", loopCondition);
            instrInfo.setLoopIfCondition(loopCondition);
        }

        auto foundBB = [&](llvm::BasicBlock* bb) -> std::string
        {
            std::string result = "";
            // for(const auto& v: visited)
            // {
            //     if(std::find(closingBraces.begin(), closingBraces.end(), v) != closingBraces.end())
            //     {
            //         result = v;
            //         break;
            //     }
            // }
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
            if(isBBConditional(foundBB(bb)))
            {
                // instrInfo.setSHouldWriteElse(true);
                // numSpaces += numSpacesForBlock;
                // closingBraces.push_back(getSecondBranchOfBrInst(bb));
            }
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
            repo.insert(instrInfo);
        }

        populateInstructionInfoRepoForBasicBlock(repo, bb, numSpaces, instrInfo);
        
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
        if(!instrInfo.getLoopIfCondition().empty() && !isLoopSelfContained(bbInfo, bb))
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

    for(auto instr: expandedInstructions)
    {
        logger->error("[generate] expandedInstructions: [{}, {}] -> {}", instr.getBBName(), instr.getInstrName(), instr.getExpandedInstr());
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
            fnBody += codeGen::LoopHandler::generateLoop(condition, indentLevel, loopType);
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