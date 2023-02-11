#include "codeGen/CodeGeneration.h"
#include "codeGen/BranchConditionalGen.h"
#include "codeGen/GenerateFnHeader.h"
#include "codeGen/RenameVariables.h"
#include "codeGen/LoopGen.h"
#include "codeGen/instructions/Instruction.h"
#include "logger/LoggerManager.h"
#include "utils/CodeGenUtils.h"


#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/ErrorOr.h"
#include "llvm/IR/CFG.h"
#include "llvm/Analysis/PostDominators.h"
#include "llvm/IR/Function.h"
#include "llvm/ADT/GraphTraits.h"
#include "llvm/ADT/PostOrderIterator.h"
#include <llvm/Analysis/LoopInfo.h>
#include <llvm/IR/Dominators.h>
#include <llvm/Pass.h>
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Analysis/LoopPass.h"
#include <llvm/ADT/PostOrderIterator.h>

#include <stack>
#include <map>
#include <vector>


codeGen::CodeGeneration::CodeGeneration(const std::string& irFile, std::unordered_map<std::string, udm::FuncInfo> fnInfoMap) 
: irFile(irFile), 
funcInfoMap(fnInfoMap) 
{
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}

void codeGen::CodeGeneration::generate() {
    logger->info("Generating code for IR file: " + irFile);

    llvm::LLVMContext context;
    llvm::SMDiagnostic error;

    std::unique_ptr<llvm::Module> mod = llvm::parseIRFile(irFile, error, context);

    if (!mod) {
        logger->critical("Couldn't open the file with LLVM IR!");
        exit(1);
    }

    for(llvm::Function &f: mod->functions())
    {
        auto fName = f.getName().str();
        auto funcInfo = funcInfoMap[fName];
        processFunction(f, funcInfo);
    }
}

void codeGen::CodeGeneration::processFunction(llvm::Function& f, const udm::FuncInfo& funcInfo)
{
    std::vector<std::string> functionNames = {"calc_sum", 
    "fibo", "main", "n_way_conditional_switch", "while_pre_tested_loop",
    "while_post_tested_loop", "two_way"
    };
    
    if(std::find(functionNames.begin(), functionNames.end(), f.getName().str()) == functionNames.end())
    {
        return;
    }

    std::string decompiledFunction = "\n";
    codeGen::GenerateFnHeader fnHeaderGenerator(f);
    decompiledFunction += fnHeaderGenerator.generate();

    codeGen::RenameVariables renameVariables(f);
    auto aliasMap = renameVariables.rename();

    for(const auto& [key, value]: aliasMap)
    {
        logger->info("Alias Key: {}, Value: {}", key, value);
    }

    uint64_t numSpaces = 4, numSpacesForBlock = 4;
    llvm::ReversePostOrderTraversal<llvm::Function*> rpot(&f);

    for(auto& bb: rpot)
    {
       for(auto& inst: *bb)
       {
           decompiledFunction += utils::CodeGenUtils::getSpaces(numSpaces);
           auto instruction = codeGen::Instruction::getInstruction(inst, numSpaces);
           if(instruction)
           {
               decompiledFunction += instruction->toString();
               decompiledFunction += ";\n";
           }
       }
    }

    decompiledFunction += "}\n";
    logger->error("Decompiled function: {}", decompiledFunction);
}

std::string codeGen::CodeGeneration::generateInstruction(const std::string& key, const std::pair<std::string,
    codeGen::GeneratedInstrType>& instrPair,
    const std::unordered_map<std::string, uint64_t>& noOfUses    
)
{
    auto instrType = instrPair.second;

    if(instrType == codeGen::GeneratedInstrType::ALLOCA)
    {
        return instrPair.first + ";";
    }

    if(instrType == codeGen::GeneratedInstrType::BINARY_OP)
    {
        if(isValueSubstring(instrPair.first))
        {
            return "";
        }
        return key + " = " + instrPair.first + ";";
    }

    if(instrType == codeGen::GeneratedInstrType::STORE)
    {
        // return "";
        return key + " = " + instrPair.first + ";";
    }

    if(instrType == codeGen::GeneratedInstrType::LOAD)
    {
        if(noOfUses.at(key) == 1)
        {
            return "";
        }
        return key + " = " + instrPair.first + ";";
        // return "";
    }

    if(instrType == codeGen::GeneratedInstrType::RETURN)
    {
        // TO DO: Support multiple return values
        return "";
    }

    if(instrType == codeGen::GeneratedInstrType::NONE)
    {
        logger->error("Instruction type has not been set for instruction: {}", instrPair.first);
    }

    return "";
}

bool codeGen::CodeGeneration::isValueSubstring(const std::string& value)
{
    for(auto& [key, pair]: instructionMap)
    {
        if( value != pair.first && pair.first.find(value) != std::string::npos)
        {
            return true;
        }
    }
    return false;
}

std::string codeGen::CodeGeneration::generateConditionalBranch(llvm::BasicBlock* bb, int numSpaces, const udm::FuncInfo& funcInfo)
{
    std::string result = "";
    auto bbInfo = funcInfo.getBBInfo(bb->getName().str());

    if(bbInfo.getLoopType() == udm::BBInfo::LoopType::NONE && !bbInfo.getFollowNode().empty())
    {
        auto expandedInstr = expandInstruction(&bb->back(), 0);
        if(expandedInstr.empty())
        {
            return result;
        }
        result += codeGen::BranchConditionalGen::generateConditional(expandedInstr, numSpaces, false);  
    }
    return result;
}

std::string codeGen::CodeGeneration::generateLoop(llvm::BasicBlock* bb, int numSpaces, const udm::FuncInfo& funcInfo)
{
    std::string result = "";
    auto loopType = funcInfo.getBBInfo(bb->getName().str()).getLoopType();
    if(loopType == udm::BBInfo::LoopType::NONE)
    {
        return result;
    }

    auto expandedInstr = expandInstruction(&bb->back(), 0);
    if(expandedInstr.empty())
    {
        return result;
    }

    result += codeGen::LoopGen::generateLoop(expandedInstr, numSpaces, loopType);
    return result;
}

std::unordered_map<std::string, uint64_t> codeGen::CodeGeneration::noOfUses(llvm::Function& f)
{
    std::unordered_map<std::string, uint64_t> result;
    auto rpot = llvm::ReversePostOrderTraversal<llvm::Function*>(&f);
    for(auto& bb: rpot)
    {
        for(auto& inst: *bb)
        {
            for(auto& op: inst.operands())
            {
                if(op->hasName())
                {
                    auto opName = op->getName().str();
                    if(result.find(opName) == result.end())
                    {
                        result.insert_or_assign(opName, 1);
                    }
                    else
                    {
                        result[opName]++;
                    }
                }
            }
        }
    }
    return result;
}

std::string codeGen::CodeGeneration::expandInstruction(llvm::Instruction* instr, int numSpaces)
{
    std::string currentInstrString = "";
    auto instrObj = codeGen::Instruction::getInstruction(*instr, 0);
    if(instrObj)
    {
        currentInstrString = instrObj->toString();
    }
    else
    {
        logger->error("[expandInstruction] Instruction: {} not found", instr->getOpcodeName());
        return "";
    }

    for(auto& op: instr->operands())
    {
        logger->info("[expandInstruction] Instruction string: {}", currentInstrString);
        std::string opName = "";
        if(!op->hasName())
        {
            continue;
        }
        opName.empty() ? opName = op->getName().str() : opName;
        if(instructionMap.find(opName) == instructionMap.end())
        {
            logger->error("[expandInstruction] Operand: {} not found", opName);
            continue;
        }

        logger->info("[expandInstruction] Operand: {} found", opName);
        auto opValue = instructionMap[opName].first;

        // If the operand is a substring of another operand, then we need to add brackets
        // else it means that we make a replacement of the operand with its value
        // TODO: Should repalce with a function that is more generic and takes as input the operand and the instruction
        if(opValue.find(" ") != std::string::npos)
        {
            opValue = "(" + opValue + ")";
        }
        
        if(currentInstrString.find(opName) != std::string::npos)
        {
            logger->error("[expandInstruction] Operand: {} value: {}", opName, opValue);
            currentInstrString.replace(currentInstrString.find(opName), opName.length(), opValue);
        }
    }

    if(currentInstrString.empty())
    {
        logger->error("[expandInstruction] ExpandINstruction returned empty string");
    }
    logger->info("[expandInstruction] Weird expand: {}", currentInstrString);
    return currentInstrString;
}

void codeGen::CodeGeneration::fillInstructionMap(llvm::BasicBlock* bb, int numSpaces)
{
    for(auto& inst: *bb)
    {
        logger->info("Instruction: {}", inst.getOpcodeName());
        auto instruction = codeGen::Instruction::getInstruction(inst, numSpaces);

        // skip the Jump instruction
        if(&inst == &bb->back() && inst.getOpcode() == llvm::Instruction::Br)
        {
            continue;
        }

        if(instruction)
        {
            auto expandedInstr = expandInstruction(&inst, numSpaces);
            if(expandedInstr.empty())
            {
                logger->error("Expanded instruction is empty");
                continue;
            }
            logger->error("Expanded instruction: {}", expandedInstr);

            std::string instrName = inst.getName().str();
            if(!inst.hasName())
            {
                auto pair = instructionMapping(&inst);
                instrName = pair.first;
                auto instrValue = pair.second;

                if(!instrValue.empty())
                {
                    instructionMap.insert_or_assign(instrName, 
                        std::make_pair<std::string, codeGen::GeneratedInstrType>(std::move(instrValue), getInstrTypeToGenerate(&inst)));
                    continue;
                }
            }

            if(auto loadInstr = llvm::dyn_cast<llvm::LoadInst>(&inst))
            {
                auto opName = loadInstr->getOperand(0)->getName().str();
                instructionMap.insert_or_assign(instrName, 
                    std::make_pair<std::string, codeGen::GeneratedInstrType>(std::move(opName), codeGen::GeneratedInstrType::LOAD));
                continue;
            }

            instructionMap.insert_or_assign(instrName, 
                std::make_pair<std::string, codeGen::GeneratedInstrType>(std::move(expandedInstr), getInstrTypeToGenerate(&inst)));
        }
    }
}

std::pair<std::string, std::string> codeGen::CodeGeneration::instructionMapping(llvm::Instruction* instr)
{
    if( auto storeInstr = llvm::dyn_cast<llvm::StoreInst>(instr))
    {
        auto op1Instr = llvm::dyn_cast<llvm::Instruction>(storeInstr->getOperand(0));
        auto op2Instr = llvm::dyn_cast<llvm::Instruction>(storeInstr->getOperand(1));
        if(op1Instr && op2Instr)
        {
            auto val1 = expandInstruction(op1Instr, 0);
            auto val2 = expandInstruction(op2Instr, 0);
            if(val1.size() > MAX_INSTR_SIZE || val1.empty())
            {
                val1 = storeInstr->getOperand(0)->getName().str();
            }

            if(val2.size() > MAX_INSTR_SIZE || val2.empty())
            {
                val2 = storeInstr->getOperand(1)->getName().str();
            }
            return std::make_pair<std::string, std::string> (std::move(val2), std::move(val1));
        }
    }

    if( auto retInstr = llvm::dyn_cast<llvm::ReturnInst>(instr))
    {
        auto op1Instr = llvm::dyn_cast<llvm::Instruction>(retInstr->getOperand(0));
        if(op1Instr)
        {
            auto val1 = retInstr->getOperand(0)->getName().str();
            return std::make_pair<std::string, std::string> ("", std::move(val1));
        }
    }

    return std::make_pair<std::string, std::string> ("", "");
}

codeGen::GeneratedInstrType codeGen::CodeGeneration::getInstrTypeToGenerate(llvm::Instruction* instr)
{
    if(instr->getOpcode() == llvm::Instruction::Alloca)
    {
        return codeGen::GeneratedInstrType::ALLOCA;
    }

    if(instr->getOpcode() == llvm::Instruction::Store)
    {
        return codeGen::GeneratedInstrType::STORE;
    }

    if(instr->getOpcode() == llvm::Instruction::Load)
    {
        return codeGen::GeneratedInstrType::LOAD;
    }

    if(instr->isBinaryOp())
    {
        return codeGen::GeneratedInstrType::BINARY_OP;
    }

    if(instr->isTerminator() && instr->getOpcode() == llvm::Instruction::Ret)
    {
        return codeGen::GeneratedInstrType::RETURN;
    }

    return codeGen::GeneratedInstrType::NONE;
}