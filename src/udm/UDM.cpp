#include "udm/UDM.h"

#include "udm/Interval.h"
#include "udm/IntervalGraph.h"
#include "logger/LoggerManager.h"

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

#include <spdlog/spdlog.h>

#include <vector>
#include <iostream>
#include <set>

udm::UDM::UDM(const std::string& IRFile)
: irFile(IRFile)
{
    logger = logger::LoggerManager::getInstance()->getLogger("udm");
}

void udm::UDM::execute()
{
    llvm::LLVMContext context;
    llvm::SMDiagnostic error;

    std::unique_ptr<llvm::Module> mod = llvm::parseIRFile(irFile, error, context);

    if (!mod) {
        logger->critical("Couldn't open the file with LLVM IR!");
        exit(1);
    }

    for(llvm::Function &f: mod->functions())
    {
        udm::FuncInfo funcInfo{f};
        llvm::PostDominatorTree dt(f);
        udm::IntervalGraph ig{dt};

        if(f.getName() == "calc_sum" || f.getName() == "fibo" || f.getName() =="main" || f.getName() == "n_way_conditional_switch"
            || f.getName() == "while_pre_tested_loop" || f.getName() == "while_post_tested_loop" || f.getName() == "two_way")
        {
            auto intv = ig.intervalsGraph(f, funcInfo);
            ig.setIntervals(intv);
            logger->info("Function name: <{}>(), length of intervals: {}", f.getName(), intv.size());
            for(auto& interval: intv)
            {
                logger->info("Interval size: {}", interval.size());
                for(auto& bb: interval.getBBlocks())
                {
                    logger->info("BB in interval: {}", bb->getName());
                }
            }

            ig.loopStructure(funcInfo);
            ig.twoWayConditionalBranch(funcInfo);
            funcInfo.print();
            // add the function information to the map to be
            // used later in code generation
            funcInfoMap.emplace(f.getName().str(), funcInfo);
        }
        
    }
}

std::unordered_map<std::string, udm::FuncInfo> udm::UDM::getFuncInfoMap()
{
    return funcInfoMap;
}

void udm::UDM::printLoops(llvm::Function &F) {
    llvm::DominatorTree DT;
    DT.recalculate(F);

    llvm::LoopInfo LI;
    LI.analyze(DT);

    for (auto I = LI.begin(), E = LI.end(); I != E; ++I) {
        auto *L = *I;
        std::cout << "Loop with header block: " << L->getHeader()->getName().str() << "\n";
        for (auto &BB : L->getBlocks()) {
            std::cout << "  Block: " << BB->getName().str() << "\n";
        }
    }
}