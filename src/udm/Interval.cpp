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

bool udm::Interval::operator==(const Interval& other) const noexcept
{
    if(bBlocks.size() != other.bBlocks.size())
    {
        return false;
    }

    for(size_t i = 0; i < bBlocks.size(); ++i)
    {
        if(bBlocks[i]->getName() != other.bBlocks[i]->getName())
        {
            return false;
        }
    }

    return true;
}

bool udm::Interval::operator!=(const Interval& other) const noexcept
{
    return !(*this == other);
}


llvm::BasicBlock* udm::Interval::operator[](size_t index) const noexcept
{
    return index > bBlocks.size() ? nullptr : bBlocks[index];
}

udm::Interval::iterator udm::Interval::begin() noexcept
{
    return bBlocks.begin();
}

udm::Interval::iterator udm::Interval::end() noexcept
{
    return bBlocks.end();
}

udm::Interval::const_iterator udm::Interval::cbegin() const noexcept
{
    return bBlocks.begin();
}

udm::Interval::const_iterator udm::Interval::cend() const noexcept
{
    return bBlocks.end();
}

udm::Interval::reverse_iterator udm::Interval::rbegin()
{
    return bBlocks.rbegin();
}

udm::Interval::reverse_iterator udm::Interval::rend()
{
    return bBlocks.rend();
}

udm::Interval::const_reverse_iterator udm::Interval::crbegin()
{
    return bBlocks.rbegin();
}

udm::Interval::const_reverse_iterator udm::Interval::crend()
{
    return bBlocks.rend();
}

void udm::Interval::appendBack(const Interval& other)
{
    bBlocks.insert(bBlocks.end(), other.bBlocks.begin(), other.bBlocks.end());
}

void udm::Interval::appendFront(const Interval& other)
{
    bBlocks.insert(bBlocks.begin(), other.bBlocks.begin(), other.bBlocks.end());
}


