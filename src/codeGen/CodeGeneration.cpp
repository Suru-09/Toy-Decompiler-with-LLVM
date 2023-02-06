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

    auto appendInstrToDecompFN = [&](llvm::Instruction& inst, uint64_t numSpaces)
    {
        auto instr = codeGen::Instruction::getInstruction(inst, numSpaces);
        if(instr)
        {
            decompiledFunction += instr->toString();
        }
    };

    uint64_t counter = 0;
    const std::string var = "var";
    std::stack<std::string> bbStack;
    std::vector<std::string> visited;

    bool printFirstInst = true, printLastInst = true;

    llvm::ReversePostOrderTraversal<llvm::Function*> rpot(&f);
    for(auto& bb: rpot)
    {
        // for(auto& inst: *bb)
        // {
        //     inst.setName(var + std::to_string(counter++));
        // }

        auto bbName = bb->getName().str();
        auto bbInfo = funcInfo.getBBInfo(bbName);
        logger->info("Basic block: {}", bb->getName());
        logger->error("BB Info: {}", bbInfo.toString());

        // generate conditional branch
        if(bbInfo.getLoopType() == udm::BBInfo::LoopType::NONE && !bbInfo.getFollowNode().empty())
        {
            auto instr = codeGen::Instruction::getInstruction(bb->front(), numSpaces);
            
            std::string branchString = "";
            if(!bbStack.empty() && bbName == bbStack.top())
            {
                branchString = codeGen::BranchConditionalGen::generateConditional(instr, numSpaces, false);
            }
            else
            {
                branchString = codeGen::BranchConditionalGen::generateConditional(instr, numSpaces, false);
            }
            
            bbStack.push(bbInfo.getFollowNode());
            decompiledFunction += branchString;
            numSpaces += numSpacesForBlock;
            printFirstInst = false;
        }

        // generate loop
        if(bbInfo.getLoopType() != udm::BBInfo::LoopType::NONE)
        {
            auto instr = codeGen::Instruction::getInstruction(bb->back(), numSpaces);

            std::string loopString = codeGen::LoopGen::generateLoop(instr, numSpaces, bbInfo.getLoopType());
            decompiledFunction += loopString;
            numSpaces += numSpacesForBlock;
            bbStack.push(bbInfo.getFollowNode());
            printFirstInst = false;
        }


        while(!bbStack.empty() && bbName == bbStack.top())
        {
            logger->error("Equality: {} == {} -> [{}]", bbName, bbStack.top(), bbName == bbStack.top());
            numSpaces -= numSpacesForBlock;
            decompiledFunction += utils::CodeGenUtils::getSpaces(numSpaces) + "}\n";
            bbStack.pop();
        }
        
        for(auto& inst: *bb)
        {
            logger->info("Instruction: {}", inst.getOpcodeName());
            auto instruction = codeGen::Instruction::getInstruction(inst, numSpaces);

            // skip the Jump instruction
            if(&inst == &bb->back() && inst.getOpcode() == llvm::Instruction::Br)
            {
                continue;
            }

          
            if(!printFirstInst)
            {
                printFirstInst = true;
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

        for(auto& [key, value]: instructionMap)
        {
            if(!isValueSubstring(value) && std::find(visited.begin(), visited.end(), key) == visited.end())
            {
                decompiledFunction += utils::CodeGenUtils::getSpaces(numSpaces);
                decompiledFunction += key + " = " + value;
                visited.push_back(key);
                decompiledFunction += "\n";
            }    
        }

        printFirstInst = true;
        printLastInst = true;
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

codeGen::CodeGeneration::CodeGeneration(const std::string& irFile, std::unordered_map<std::string, udm::FuncInfo> fnInfoMap) 
: irFile(irFile), 
funcInfoMap(fnInfoMap) 
{
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}