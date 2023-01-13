#include "udm/FunctionsAnalysis.h"

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

std::string udm::FunctionsAnalysis::instructionToString(llvm::Instruction &I)
{
   std::string buf;
   llvm::raw_string_ostream os(buf);
   I.print(os);
   os.flush();
   return buf;
}

std::vector<udm::Interval> udm::FunctionsAnalysis::intervals(llvm::Function& f)
{
    std::vector<udm::Interval> intervals;
    llvm::ReversePostOrderTraversal<llvm::Function*> rpot(&f);
    auto ri = rpot.begin();

    while(ri != rpot.end())
    {
       llvm::BasicBlock* bb = (*ri);

       Interval interval;
       interval.addBlock(bb);

       spdlog::info("BB in RPOT: {}", bb->getName());

        auto predecessors = getPredecessors(bb);
        spdlog::warn("Size of predecessors: <{}>", predecessors.size());

        while(interval.containsPredecessors(predecessors))
        {
            ++ri;
            if(ri == rpot.end())
            {
                break;
            }
            predecessors = getPredecessors(bb);
            bb = (*ri);
            interval.addBlock(bb);
        }
       
       if(ri != rpot.end())
       {
           ++ri;
       }
       spdlog::warn("Size of interval: <{}>", interval.size());
       intervals.emplace_back(interval);
    }
    return intervals;
}


std::vector<std::string> udm::FunctionsAnalysis::getPredecessors(llvm::BasicBlock* bb)
{
    std::vector<std::string> predecessors;
    for(auto pred: llvm::predecessors(bb))
    {
        predecessors.emplace_back(pred->getName());
    }

    return predecessors;
}

std::unordered_map<std::string, udm::FuncInfo> udm::FunctionsAnalysis::getFunctionsInfo() const
{
    return functionsInfo;
}