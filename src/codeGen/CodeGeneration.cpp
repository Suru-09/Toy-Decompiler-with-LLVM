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
    std::unordered_map<std::string, uint64_t> uses = noOfUses(f);

    for(auto& bb: rpot)
    {
        auto bbName = bb->getName().str();
        auto bbInfo = funcInfo.getBBInfo(bbName);
        logger->info("Basic block: {}", bb->getName());
        logger->error("BB Info: {}", bbInfo.toString());

        fillInstructionMap(bb, numSpaces);

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


        auto isKeyVisited = [&](const std::string& key) {
            return std::find(visited.begin(), visited.end(), key) != visited.end();
        };

        for(auto& [key, value]: instructionMap)
        {
            if(isKeyVisited(key))
            {
                continue;
            }

            std::string generatedInstr = generateInstruction(key, value, uses);
            if(generatedInstr.empty())
            {
                continue;
            }

            decompiledFunction += utils::CodeGenUtils::getSpaces(numSpaces);
            decompiledFunction += generatedInstr;
            decompiledFunction += "\n";
            visited.push_back(key);
        }
    }

    // print instructionMap
    logger->error("Printing instructionMap");
    for(auto& [key, value]: instructionMap)
    {
        logger->error("Key: {}, Value: {}", key, value.first);
    }

    while(!bbStack.empty())
    {
        numSpaces -= numSpacesForBlock;
        decompiledFunction += utils::CodeGenUtils::getSpaces(numSpaces) + "}\n";
        bbStack.pop();
    }

    // ! TODO: handle return instruction more elegantly
    // for now return is always the last instruction
    // and only one can exist in a function
    for(auto& [key, value]: instructionMap)
    {
        if(value.second == codeGen::GeneratedInstrType::RETURN)
        {
            decompiledFunction += utils::CodeGenUtils::getSpaces(numSpaces);
            decompiledFunction += value.first + ";\n";
            break;
        }
    }

    decompiledFunction += "}\n";
    logger->error("Decompiled function: {}", decompiledFunction);
    instructionMap.clear();
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
        return "";
        // return key + " = " + instrPair.first + ";";
    }

    if(instrType == codeGen::GeneratedInstrType::LOAD)
    {
        if(noOfUses.at(key) == 1)
        {
            return "";
        }
        // return key + " = " + instrPair.first + ";";
        return "";
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

std::string codeGen::CodeGeneration::generateFnHeader(llvm::Function& f)
{
    std::string result = "";
    result += "Fn " + f.getName().str() + "(";
    
    bool isCommaNeeded = true;
    uint64_t argCount = f.arg_size(), argIndex = 0;
    for(auto& arg: f.args())
    {
        std::string argType = utils::CodeGenUtils::typeToString(arg.getType());
        result += arg.getName().str() + ": " + argType;
        if(argIndex < argCount - 1)
        {
            result += ", ";
        }
        argIndex++;
    }

    std::string returnType = utils::CodeGenUtils::typeToString(f.getReturnType());
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
        if(!op->hasName())
        {
            logger->warn("[expandInstruction] Instruction: doesn't have a name");
            continue;
        }
        
        auto opName = op->getName().str();
        if(instructionMap.find(opName) == instructionMap.end())
        {
            logger->error("[expandInstruction] Operand: {} not found", opName);
            continue;
        }

        logger->info("[expandInstruction] Operand: {} found", opName);
        auto opValue = instructionMap[opName].first;
        opValue = "(" + opValue + ")";
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

            // if(!inst.hasName())
            // {
            //     logger->error("Instruction doesn't have a name");
            //     continue;
            // }

            instructionMap.insert_or_assign(inst.getName().str(), 
                std::make_pair<std::string, codeGen::GeneratedInstrType>(std::move(expandedInstr), getInstrTypeToGenerate(&inst)));
        }
    }
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

codeGen::CodeGeneration::CodeGeneration(const std::string& irFile, std::unordered_map<std::string, udm::FuncInfo> fnInfoMap) 
: irFile(irFile), 
funcInfoMap(fnInfoMap) 
{
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}