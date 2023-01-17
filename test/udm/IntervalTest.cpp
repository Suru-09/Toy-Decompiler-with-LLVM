#include "gtest/gtest.h"

#include "udm/Interval.h"

#include <llvm/IR/BasicBlock.h>
#include<llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"


class IntervalTest : public ::testing::Test
{
    void setUp()
    {
        module = new llvm::Module("IntervalTest", context);
        llvm::FunctionType* functionType = llvm::FunctionType::get(llvm::Type::getVoidTy(context), false);
        function = llvm::Function::Create(functionType, llvm::Function::ExternalLinkage, "testInterval", module);
    }

    void tearDown()
    {
        free(module);
        free(function);
    }

public:
    llvm::BasicBlock* createBB(const std::string& name)
    {
        return llvm::BasicBlock::Create(context, name, function);
    }
private:
    llvm::LLVMContext context;
    llvm::Module* module = nullptr;
    llvm::Function* function = nullptr;
};

TEST_F(IntervalTest, ContainsBlocks)
{
    udm::Interval interval;
    llvm::BasicBlock* bb1 = createBB("bb1");
    llvm::BasicBlock* bb2 = createBB("bb2");
    llvm::BasicBlock* bb3 = createBB("bb3");

    interval.addBlock(bb1);
    interval.addBlock(bb2);
    interval.addBlock(bb3);

    // check if the interval contains all predecessors
    std::vector<std::string> pred = {"bb1", "bb2", "bb3"};
    ASSERT_TRUE(interval.containsBlocks(pred));

    // One predecessor is not in the interval
    pred = {"bb1", "bb2", "bb4"};
    ASSERT_FALSE(interval.containsBlocks(pred));

    // Two predecessors are not in the interval
    pred = {"bb1", "bb4", "bb5"};
    ASSERT_FALSE(interval.containsBlocks(pred));

    // Empty predecessor list
    pred = {};
    ASSERT_TRUE(interval.containsBlocks(pred));
}

TEST_F(IntervalTest, AddBlock)
{
    udm::Interval interval;
    llvm::BasicBlock* bb1 = createBB("bb1");
    llvm::BasicBlock* bb2 = createBB("bb2");
    llvm::BasicBlock* bb3 = createBB("bb3");

    // add a block to the interval.
    EXPECT_TRUE(interval.addBlock(bb1));
    EXPECT_EQ(interval.getBlock("bb1"), bb1);

    // add the same block again
    EXPECT_FALSE(interval.addBlock(bb1));
    EXPECT_EQ(interval.getBlock("bb1"), bb1);

    // add a second block
    EXPECT_TRUE(interval.addBlock(bb2));
    EXPECT_EQ(interval.getBlock("bb2"), bb2);
}

TEST_F(IntervalTest, GetBlock)
{
    udm::Interval interval;
    llvm::BasicBlock* bb1 = createBB("bb1");
    llvm::BasicBlock* bb2 = createBB("bb2");

    // add a block to the interval.
    interval.addBlock(bb1);

    // get block by name
    EXPECT_EQ(interval.getBlock("bb1"), bb1);

    // get block by index
    EXPECT_EQ(interval.getBlock(0), bb1);

    EXPECT_EQ(interval.getBlock("bb2"), nullptr);
}

TEST_F(IntervalTest, ContainsBlock)
{
    udm::Interval interval;
    llvm::BasicBlock* bb1 = createBB("bb1");
    llvm::BasicBlock* bb2 = createBB("bb2");
    llvm::BasicBlock* bb3 = createBB("bb3");
    llvm::BasicBlock* bb4 = createBB("bb4");
    llvm::BasicBlock* bb5 = createBB("bb5");

    interval.addBlock(bb1);
    interval.addBlock(bb2);
    interval.addBlock(bb3);

    ASSERT_TRUE(interval.containsBlock(bb1));
    ASSERT_TRUE(interval.containsBlock("bb2"));
    ASSERT_TRUE(interval.containsBlock(bb3));

    ASSERT_FALSE(interval.containsBlock("bb5"));
    ASSERT_FALSE(interval.containsBlock(bb5));
    ASSERT_FALSE(interval.containsBlock(bb4));
}

// test interval.appendBack()
TEST_F(IntervalTest, AppendBack)
{
    udm::Interval interval1;
    llvm::BasicBlock* bb1 = createBB("bb1");
    llvm::BasicBlock* bb2 = createBB("bb2");
    llvm::BasicBlock* bb3 = createBB("bb3");

    interval1.addBlock(bb1);
    interval1.addBlock(bb2);
    interval1.addBlock(bb3);

    udm::Interval interval2;
    llvm::BasicBlock* bb4 = createBB("bb4");
    llvm::BasicBlock* bb5 = createBB("bb5");
    llvm::BasicBlock* bb6 = createBB("bb6");

    interval2.addBlock(bb4);
    interval2.addBlock(bb5);
    interval2.addBlock(bb6);

    interval1.appendBack(interval2);

    std::vector<std::string> pred = {"bb1", "bb2", "bb3", "bb4", "bb5", "bb6"};
    ASSERT_TRUE(interval1.containsBlocks(pred));
}

TEST_F(IntervalTest, AppendFront)
{
    udm::Interval interval1;
    llvm::BasicBlock* bb1 = createBB("bb1");
    llvm::BasicBlock* bb2 = createBB("bb2");
    llvm::BasicBlock* bb3 = createBB("bb3");

    interval1.addBlock(bb1);
    interval1.addBlock(bb2);
    interval1.addBlock(bb3);

    udm::Interval interval2;
    llvm::BasicBlock* bb4 = createBB("bb4");
    llvm::BasicBlock* bb5 = createBB("bb5");
    llvm::BasicBlock* bb6 = createBB("bb6");

    interval2.addBlock(bb4);
    interval2.addBlock(bb5);
    interval2.addBlock(bb6);

    interval1.appendFront(interval2);

    std::vector<std::string> pred = {"bb4", "bb5", "bb6", "bb1", "bb2", "bb3"};
    ASSERT_TRUE(interval1.containsBlocks(pred));
}

TEST_F(IntervalTest, EqualOperator)
{
    llvm::BasicBlock* bb1 = createBB("bb1");
    llvm::BasicBlock* bb2 = createBB("bb2");
    llvm::BasicBlock* bb3 = createBB("bb3");
    llvm::BasicBlock* bb4 = createBB("bb4");
    llvm::BasicBlock* bb5 = createBB("bb5");
    llvm::BasicBlock* bb6 = createBB("bb6");

    udm::Interval interval1;
    interval1.addBlock(bb1);
    interval1.addBlock(bb2);
    interval1.addBlock(bb3);

    udm::Interval interval2;
    interval2.addBlock(bb4);
    interval2.addBlock(bb5);
    interval2.addBlock(bb6);

    udm::Interval interval3;
    interval3.addBlock(bb1);
    interval3.addBlock(bb2);
    interval3.addBlock(bb3);

    ASSERT_TRUE(interval1 != interval2);
    ASSERT_FALSE(interval1 != interval3);

    ASSERT_TRUE(interval1 == interval3);
    ASSERT_FALSE(interval1 == interval2);
}
