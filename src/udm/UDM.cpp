#include "udm/UDM.h"

#include "udm/FunctionsAnalysis.h"
#include "udm/Interval.h"

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

void udm::UDM::execute()
{
    llvm::LLVMContext context;
    llvm::SMDiagnostic error;

    std::unique_ptr<llvm::Module> mod = llvm::parseIRFile(irFile, error, context);

    if (!mod) {
        spdlog::critical("Couldn't open the file with LLVM IR!");
        exit(1);
    }

    udm::FunctionsAnalysis fAnalysis;

    for(llvm::Function &f: mod->functions())
    {
        udm::FuncInfo funcInfo;
        if(f.getName() == "calc_sum" || f.getName() == "fibo" || f.getName() =="main" || f.getName() == "n_way_conditional_switch")
        {
            auto intv = udm::Interval::intervals(f, funcInfo);
            spdlog::info("Function name: <{}>(), length of intervals: {}", f.getName(), intv.size());
            for(auto& interval: intv)
            {
                spdlog::info("Interval size: {}", interval.size());
                for(auto& bb: interval.getBBlocks())
                {
                    spdlog::info("BB in interval: {}", bb->getName());
                }
            }
        }

    }
}
