#include "udm/Interval.h"


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