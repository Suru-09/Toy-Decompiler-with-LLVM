#include "udm/cfa/CFG.h"

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

#include <spdlog/spdlog.h>

#include <vector>
#include <iostream>

udm::CFG::CFG(const std::string& IRFile)
: irFile(IRFile)
{
}

std::string udm::CFG::instructionToString(llvm::Instruction &I) {
   std::string buf;
   llvm::raw_string_ostream os(buf);
   I.print(os);
   os.flush();
   return buf;
}

std::vector<std::vector<llvm::BasicBlock *>> udm::CFG::intervals(llvm::Function& f)
{
    std::vector<std::vector<llvm::BasicBlock*>> intervals;
    std::vector<llvm::BasicBlock*> headers;
    headers.emplace_back(&*f.begin());
    
    llvm::ReversePostOrderTraversal<llvm::Function*> rpot(&f);
    auto ri = rpot.begin();
    while(ri != rpot.end())
    {
       llvm::BasicBlock* bb = (*ri);
       spdlog::info("BB in RPOT: {}", bb->getName());
       std::vector<llvm::BasicBlock*> interval;
       interval.push_back(bb);

        std::vector<llvm::BasicBlock*> predeces = getPredecessors(bb);
        for(const auto& x: predeces)
       {
            spdlog::warn("predeces: {}", x->getName());
       }

        while(allPredecessorsInInterval(getPredecessors(bb), interval))
        {
            bb = (*ri);
            interval.push_back(bb);
            ++ri;
        }
       headers.emplace_back(*ri);
       intervals.emplace_back(interval);
       for(const auto& x: interval)
       {
            spdlog::critical("Interval: {}", x->getName());
       }
       interval.clear();
       ++ri;
    }
    return intervals;
}

bool udm::CFG::allPredecessorsInInterval(std::vector<llvm::BasicBlock*> pred,std::vector<llvm::BasicBlock*> interval)
{
    for(auto bb: pred)
    {
        if(std::find(interval.begin(), interval.end(), bb) == interval.end())
            return false;
    }
    return true;
}

std::vector<llvm::BasicBlock*> udm::CFG::getPredecessors(llvm::BasicBlock* bb)
{
    std::vector<llvm::BasicBlock*> predecessors;
    for(auto pred: llvm::predecessors(bb))
    {
        predecessors.emplace_back(pred);
    }

    return predecessors;
}


void udm::CFG::execute()
{
    llvm::LLVMContext context;
    llvm::SMDiagnostic error;

    std::unique_ptr<llvm::Module> mod = llvm::parseIRFile(irFile, error, context);

    if (!mod) {
        spdlog::critical("Couldn't open the file with LLVM IR!");
        exit(1);
    }

    for(llvm::Function &f: mod->functions())
    {
        if(f.getName() == "calc_sum")
        {
            // spdlog::info("Function name: {}", f.getName());
            // for (llvm::BasicBlock &bb : f) {
            //     spdlog::info("Basick block : {}", bb.getName());
            //     for (llvm::Instruction &instr : bb) {
            //         spdlog::info("Instruction: {}", instructionToString(instr));
            //     }
            // }
            spdlog::info("Length of intervals: {}", intervals(f).size());
        }

    }
}
