#ifndef __INTERVAL_H__
#define __INTERVAL_H__

#include <iostream>
#include <vector>

#include <llvm/IR/BasicBlock.h>


namespace udm
{

class Interval {
public:
    Interval() = default;

    /**
     * @brief Deleted copy constructor and copy assignment operator.
     * We do not need to move an Interval object !!!.
    */
    Interval&& operator=(const Interval&& other) = delete;
    Interval(const Interval&& other) = delete;
    /**
     * @param bb: BasicBlock to be added to the interval.
     * @brief Adds an element at the end of the interval, if the element doesn't exist
     * in the interval.
     * @return true if the element was added, false otherwise.
    */
    bool addBlock(llvm::BasicBlock* bb);

    /**
     * @param bbName: name of the element to be returned.
     * @brief Returns the element with the given name.
     * @return the element with the given name if it exists, nullptr otherwise.
    */
    llvm::BasicBlock* getBlock(const std::string& bbName) const noexcept;


    /**
     * @param index: index of the element to be returned.
     * @brief Returns the element at the given index.
     * @return the element at the given index if it exists, nullptr otherwise.
    */
    llvm::BasicBlock* getBlock(size_t index) const noexcept;

    llvm::BasicBlock* getFirstBlock() const noexcept;
    llvm::BasicBlock* getLastBlock() const noexcept;
    size_t size() const noexcept;
    bool isEmpty() const noexcept;
    std::vector<llvm::BasicBlock*> getBBlocks() const noexcept;
    std::vector<llvm::BasicBlock*> setBBlocks(std::vector<llvm::BasicBlock*> bbs);
private:
    std::vector<llvm::BasicBlock*> bBlocks;
};

} // namespace udm  

#endif