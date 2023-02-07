#include "codeGen/CodeGeneration.h"
#include "codeGen/BranchConditionalGen.h"
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

    std::string decompiledFunction = "\n" + generateFnHeader(f);
    uint64_t numSpaces = 4, numSpacesForBlock = 4;
    std::stack<std::string> bbStack;
    std::vector<std::string> visited;

    llvm::ReversePostOrderTraversal<llvm::Function*> rpot(&f);
    auto uses = noOfUses(f);
    for(auto& bb: rpot)
    {
        auto bbName = bb->getName().str();
        auto bbInfo = funcInfo.getBBInfo(bbName);
        logger->info("Basic block: {}", bb->getName());
        logger->error("BB Info: {}", bbInfo.toString());

        // generate conditional branch
        std::string branchString = generateConditionalBranch(bb, numSpaces, funcInfo);
        if(!branchString.empty())
        {
            bbStack.push(bbInfo.getFollowNode());
            decompiledFunction += branchString;
            numSpaces += numSpacesForBlock;
        }

        // generate loop
        std::string loopString = generateLoop(bb, numSpaces, funcInfo);
        if(!loopString.empty())
        {
            decompiledFunction += loopString;
            numSpaces += numSpacesForBlock;
            bbStack.push(bbInfo.getFollowNode());
        }

        while(!bbStack.empty() && bbName == bbStack.top())
        {
            logger->error("Equality: {} == {} -> [{}]", bbName, bbStack.top(), bbName == bbStack.top());
            numSpaces -= numSpacesForBlock;
            decompiledFunction += utils::CodeGenUtils::getSpaces(numSpaces) + "}\n";
            bbStack.pop();
        }

        fillInstructionMap(bb, numSpaces);
        
        for(auto& [key, value]: instructionMap)
        {
            if(!isValueSubstring(value) && std::find(visited.begin(), visited.end(), key) == visited.end() 
                && (uses[key] > 1 || value.find("?") != std::string::npos || value.find("Integer") != std::string::npos))
            {
                decompiledFunction += utils::CodeGenUtils::getSpaces(numSpaces);
                decompiledFunction += key + " = " + value;
                visited.push_back(key);
                decompiledFunction += "\n";
            }    
        }
    }

    // print instructionMap
    logger->error("Printing instructionMap");
    for(auto& [key, value]: instructionMap)
    {
        logger->error("Key: {}, Value: {}", key, value);
    }

    while(!bbStack.empty())
    {
        numSpaces -= numSpacesForBlock;
        decompiledFunction += utils::CodeGenUtils::getSpaces(numSpaces) + "}\n";
        bbStack.pop();
    }

    decompiledFunction += "}\n";
    logger->error("Decompiled function: {}", decompiledFunction);
    instructionMap.clear();
}

bool codeGen::CodeGeneration::isValueSubstring(const std::string& value)
{
    for(auto& [key, value]: instructionMap)
    {
        if(value.find(key) != std::string::npos)
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
        auto instr = codeGen::Instruction::getInstruction(bb->back(), numSpaces);
        if(instr)
        {
            result += codeGen::BranchConditionalGen::generateConditional(instr, numSpaces, false);
        }
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

std::string codeGen::CodeGeneration::generateFnHeader(llvm::Function& f)
{
    std::string result = "";
    result += "Fn " + f.getName().str() + "(";
    
    bool isCommaNeeded = true;
    uint64_t argCount = f.arg_size(), argIndex = 0;
    for(auto& arg: f.args())
    {
        std::string argType = utils::CodeGenUtils::typeToString(arg.getType()->getTypeID());
        result += arg.getName().str() + ": " + argType;
        if(argIndex < argCount - 1)
        {
            result += ", ";
        }
        argIndex++;
    }

    std::string returnType = utils::CodeGenUtils::typeToString(f.getReturnType()->getTypeID());
    result += ") -> " + returnType + "\n{\n";

    logger->info("Function header: {}", result);
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
    std::string instrName = instr->getName().str();
    if(instructionMap.find(instrName) != instructionMap.end())
    {
        return instructionMap[instrName];
    }

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
        logger->error("Instruction string: {}", currentInstrString);
        if(op->hasName())
        {
            auto opName = op->getName().str();
            if(instructionMap.find(opName) != instructionMap.end())
            {
                auto opValue = instructionMap[opName];
                opValue = "(" + opValue + ")";
                // replaceAll not defined use another functions from standard library
                if(currentInstrString.find(opName) != std::string::npos)
                {
                    currentInstrString.replace(currentInstrString.find(opName), opName.length(), opValue);
                }
            }
        }
        else
        {
            logger->error("[expandInstructionRecursive] Instruction: doesn't have a name");
        }    
    }

    if(currentInstrString.empty())
    {
        logger->error("ExpandINstruction returned empty string");
    }
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
            logger->error("Expanded instruction: {}", expandedInstr);
            if(!expandedInstr.empty())
            {
                instructionMap.insert_or_assign(inst.getName().str(), expandedInstr);
            }
        }
    }
}

codeGen::CodeGeneration::CodeGeneration(const std::string& irFile, std::unordered_map<std::string, udm::FuncInfo> fnInfoMap) 
: irFile(irFile), 
funcInfoMap(fnInfoMap) 
{
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}