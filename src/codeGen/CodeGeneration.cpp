#include "codeGen/CodeGeneration.h"
#include "logger/LoggerManager.h"
#include "codeGen/instructions/Instruction.h"

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

    llvm::ReversePostOrderTraversal<llvm::Function*> rpot(&f);
    for(auto& bb: rpot)
    {
        auto bbName = bb->getName().str();
        auto bbInfo = funcInfo.getBBInfo(bbName);
        logger->info("Basic block: {}", bb->getName());
        logger->error("BB Info: {}", bbInfo.toString());
        
        for(auto& inst: *bb)
        {
            logger->info("Instruction: {}", inst.getOpcodeName());
            auto instruction = codeGen::Instruction::getInstruction(inst);
            if(instruction)
            {
                auto str = instruction->toString();
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