#include "gtest/gtest.h"

#include "udm/IntervalGraph.h"
#include "udm/FuncInfo.h"

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

#include <iostream>
#include <memory>


class IntervalGraphTest : public ::testing::Test
{
    void setUp()
    {
    }

    void tearDown()
    {
    }

public:
    void loadModule(const std::string& path)
    {
        llvm::SMDiagnostic error;
        module = llvm::parseIRFile(path, error, context);
        if(!module)
        {
            std::cout << "Couldn't open the file with LLVM IR!" << std::endl;
            exit(1);
        }
    }

    std::vector<udm::Interval> getIntervals(const std::string& name, const std::string& modulePath)
    {
        loadModule(modulePath);
        
        for(auto& f: module->functions())
        {
            // if(f.getName() == name)
            // {
            //     // udm::FuncInfo funcInfo{f};
            //     // llvm::PostDominatorTree dt(f);
            //     // udm::IntervalGraph ig{dt};
            //     // auto intv = ig.intervalsGraph(f, funcInfo);
            //     // ig.setIntervals(intv);
            //     // return intv;
            // }
        }
        return {};
    }

    const std::string& test_fibo = "test.ll";
    const std::string& test = "../../testing_files/elfC/test.ll";
    const std::string& test_loops = "../../testing_files/elfC/loops.ll";
private:
    llvm::LLVMContext context;
    std::unique_ptr<llvm::Module> module;
};

TEST_F(IntervalGraphTest, fiboIntervalsSize)
{
    auto intervals = getIntervals("fib", test_fibo);
    //EXPECT_EQ(intervals.size(), 3);
}

// TEST_F(IntervalGraphTest, loopsIntervalsSize)
// {
//     loadModule(test_loops);
//     auto function = getFunction("while_pre_tested_loop");
//     llvm::PostDominatorTree dt(&function);
//     udm::IntervalGraph ig{dt};
//     auto intv = ig.intervalsGraph(&function);
//     ig.setIntervals(intv);
//     EXPECT_EQ(intv.size(), 3);
// }

// TEST_F(IntervalGraphTest, testIntervalsSize)
// {
//     loadModule(test);
//     auto function = getFunction("main");
//     llvm::PostDominatorTree dt(&function);
//     udm::IntervalGraph ig{dt};
//     auto intv = ig.intervalsGraph(&function);
//     ig.setIntervals(intv);
//     EXPECT_EQ(intv.size(), 3);
// }