#include "udm/Interval.h"

#include "udm/FuncInfo.h"
#include "utils/UdmUtils.h"

#include <llvm/ADT/PostOrderIterator.h>
#include <llvm/IR/CFG.h>

#include <spdlog/spdlog.h>

bool udm::Interval::containsPredecessors(const std::vector<std::string>& pred) const
{
    for(auto& bbName: pred)
    {
        // if the given basic block is not in the interval return false
        if(getBlock(bbName) == nullptr)
        {
            return false;
        }
    }
    return true;
}

bool udm::Interval::addBlock(llvm::BasicBlock* bb)
{
    auto found = std::find_if(bBlocks.begin(), bBlocks.end(), [&bb](llvm::BasicBlock* b) {
        return b->getName() == bb->getName();
    });

    if(found != bBlocks.end())
    {
        return false;
    }

    bBlocks.push_back(bb);
    return true;
}


llvm::BasicBlock* udm::Interval::getBlock(const std::string& bbName) const noexcept
{
    auto found = std::find_if(bBlocks.begin(), bBlocks.end(), [&bbName](llvm::BasicBlock* b) {
        return b->getName() == bbName;
    });

    if(found == bBlocks.end())
    {
        return nullptr;
    }

    return *(found);
}

llvm::BasicBlock* udm::Interval::getBlock(size_t index) const noexcept
{
    if(index < bBlocks.size())
    {
        return bBlocks[index];
    }
    return nullptr;
}

llvm::BasicBlock* udm::Interval::getFirstBlock() const noexcept
{
    if(!bBlocks.empty())
    {
        return bBlocks.front();
    }
    return nullptr;
}

llvm::BasicBlock* udm::Interval::getLastBlock() const noexcept
{
    if(!bBlocks.empty())
    {
        return bBlocks.back();
    }
    return nullptr;
}

size_t udm::Interval::size() const noexcept
{
    return bBlocks.size();
}

bool udm::Interval::isEmpty() const noexcept
{
    return bBlocks.empty();
}

std::vector<llvm::BasicBlock*> udm::Interval::getBBlocks() const noexcept
{
    return bBlocks;
}

std::vector<llvm::BasicBlock*> udm::Interval::setBBlocks(std::vector<llvm::BasicBlock*> bbs)
{
    bBlocks = bbs;
    return bBlocks;
}

std::vector<udm::Interval> udm::Interval::intervals(llvm::Function& f, udm::FuncInfo& funcInfo)
{
    std::vector<udm::Interval> intervals;
    std::vector<llvm::BasicBlock*> headers;
    llvm::ReversePostOrderTraversal<llvm::Function*> rpot(&f);
    auto ri = rpot.begin();

    while(ri != rpot.end())
    {
       llvm::BasicBlock* bb = (*ri);
       udm::Interval interval;

       // the first basic block in a function is always a header
       if(headers.empty())
       {
            headers.push_back(bb);
       }
       // also a header is also contained in the interval
       interval.addBlock(headers.back());
       interval.addBlock(bb);

        auto predecessors = utils::UdmUtils::getPredecessors(bb);
        spdlog::debug("Size of predecessors: <{}>", predecessors.size());

        // If there exists a header after the current interval, the last element of
        // the while loop should become the new header, therefore we need to keep track
        // if the final element was processed or not
        bool lastElementWasInInterval = false;
        while(interval.containsPredecessors(predecessors))
        {
            ++ri;
            if(ri == rpot.end())
            {
                break;
            }
            bb = (*ri);
            predecessors = utils::UdmUtils::getPredecessors(bb);
            if(!interval.containsPredecessors(predecessors))
            {
                lastElementWasInInterval = true;
                break;
            }
            interval.addBlock(bb);
        }

        // if there any more basic blocks, add the next one as a header
        if(ri != rpot.end())
        {
            if(!lastElementWasInInterval)
            {
                ++ri;
            }
            
            
            if(ri != rpot.end())
            {
                llvm::BasicBlock* next = (*ri);
                headers.push_back(next);
                ++ri;
            }
        }
       spdlog::warn("Size of interval: <{}>", interval.size());
       intervals.emplace_back(interval);
    }

    // if the last interval does not contain the last header, add it
    // special case when the last basic block is an entire interval
    if(!intervals.back().containsBlock(headers.back()))
        {
            Interval inter;
            inter.addBlock(headers.back());
            intervals.emplace_back(inter);
        }
    return intervals;
}

bool udm::Interval::containsBlock(llvm::BasicBlock* bb) const noexcept
{
    auto found = std::find_if(bBlocks.begin(), bBlocks.end(), [&bb](llvm::BasicBlock* b) {
        return b->getName() == bb->getName();
    });

    if(found == bBlocks.end())
    {
        return false;
    }

    return true;
}

bool udm::Interval::containsBlock(const std::string& bbName) const noexcept
{
    auto found = std::find_if(bBlocks.begin(), bBlocks.end(), [&bbName](llvm::BasicBlock* b) {
        return b->getName() == bbName;
    });

    if(found == bBlocks.end())
    {
        return false;
    }

    return true;
}

void udm::Interval::clear() noexcept
{
    bBlocks.clear();
}
