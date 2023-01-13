#include "udm/UDM.h"

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
#include <set>

udm::UDM::UDM(const std::string& IRFile)
: irFile(IRFile)
{
}

std::string udm::UDM::instructionToString(llvm::Instruction &I) {
   std::string buf;
   llvm::raw_string_ostream os(buf);
   I.print(os);
   os.flush();
   return buf;
}

std::vector<std::set<llvm::BasicBlock *>> udm::UDM::intervals(llvm::Function& f)
{
    std::vector<std::set<llvm::BasicBlock*>> intervals;
    
    llvm::ReversePostOrderTraversal<llvm::Function*> rpot(&f);
    auto ri = rpot.begin();
    while(ri != rpot.end())
    {
       spdlog::info("The duck?");
       llvm::BasicBlock* bb = (*ri);
       std::set<llvm::BasicBlock*> interval;
       interval.emplace(bb);
       spdlog::info("BB in RPOT: {}", bb->getName());

        auto predeces = getPredecessors(bb);
        spdlog::warn("Size of predecess: {}", predeces.size());

        while(allPredecessorsInInterval(predeces, interval))
        {
            ++ri;
            if(ri == rpot.end())
            {
                break;
            }
            predeces = getPredecessors(bb);
            bb = (*ri);
            interval.emplace(bb);
        }
        
       
       if(ri != rpot.end())
       {
           ++ri;
       }
       intervals.emplace_back(interval);
       interval.clear();
    }
    return intervals;
}

bool udm::UDM::allPredecessorsInInterval(std::vector<std::string> pred, std::set<llvm::BasicBlock*> interval)
{
    for(auto& bbName: pred)
    {
        if( std::find_if(interval.begin(), interval.end(), [&](llvm::BasicBlock* elem){
            return elem->getName() == llvm::StringRef{bbName};
            }) == interval.end())
        {
            return false;
        }
    }
    return true;
}

std::vector<std::string> udm::UDM::getPredecessors(llvm::BasicBlock* bb)
{
    std::vector<std::string> predecessors;
    for(auto pred: llvm::predecessors(bb))
    {
        predecessors.emplace_back(pred->getName());
    }

    return predecessors;
}


void udm::UDM::execute()
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
        if(f.getName() == "calc_sum" || f.getName() == "fibo" || f.getName() =="main")
        {
            auto intv = intervals(f);
            spdlog::info("Length of intervals: {}", intv.size());
            for(auto& interval: intv)
            {
                spdlog::info("Interval size: {}", interval.size());
                for(auto& bb: interval)
                {
                    spdlog::info("BB in interval: {}", bb->getName());
                }
            }
        }

    }
}
