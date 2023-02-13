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
#include <llvm/IR/Dominators.h>

#include <llvm/Pass.h>
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/Scalar/SROA.h"

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
    dataFlowAnalysis();
}

void udm::UDM::cfgAnalysis(std::unique_ptr<llvm::Module> module)
{
    for(llvm::Function &f: module->functions())
    {
        udm::FuncInfo funcInfo{f};
        llvm::PostDominatorTree dt(f);
        udm::IntervalGraph ig{dt};

        if(f.getName() == "calc_sum" || f.getName() == "fibo" || f.getName() =="main" || f.getName() == "n_way_conditional_switch"
            || f.getName() == "while_pre_tested_loop" || f.getName() == "while_post_tested_loop" || f.getName() == "two_way" || f.getName() == "for_loop")
        {
        }
        else
        {
            continue;
        }

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

void udm::UDM::dataFlowAnalysis()
{
    llvm::LLVMContext context;
    llvm::SMDiagnostic error;

    std::string optimizedIRFile = irFile.size() > 2 ? irFile.substr(0, irFile.size() - 3) + "_optimized.ll" : irFile;
    std::string optimizations = "--sccp --reassociate --instcombine --dce --dse -simplifycfg --instnamer ";
    std::string command = "opt " + optimizations + irFile +  " -S > " + optimizedIRFile;
    system(command.c_str());

   
    std::unique_ptr<llvm::Module> module = llvm::parseIRFile(optimizedIRFile, error, context);

    if (!module) {
        logger->critical("Couldn't open the file with LLVM IR!(CFG Analysis)");
        exit(1);
    }

    cfgAnalysis(std::move(module));
}


std::unordered_map<std::string, udm::FuncInfo> udm::UDM::getFuncInfoMap()
{
    return funcInfoMap;
}