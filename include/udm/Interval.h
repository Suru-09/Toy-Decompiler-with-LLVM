#ifndef __INTERVAL_H__
#define __INTERVAL_H__

#include <iostream>
#include <vector>

#include <llvm/IR/BasicBlock.h>
#include "FuncInfo.h"


namespace udm
{

/**
 * @brief Class that represents an interval of basic blocks.
 * An interval is a larger construct that can contain multiple basic blocks,
 * and is used to represent a more complex section of code, such as a loop or a conditional statement.
*/
class Interval {
public:
    Interval() = default;
    
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


    /**
     * @param pred: vector of the predecessors of a block.
     * @brief Checks if all the predecessors are in the interval.
     * @return true  if all the predecessors are in the interval, false otherwise.
    */
    bool containsPredecessors(const std::vector<std::string>& pred) const;

    /**
     * @param bb: BasicBlock to be checked.
     * @brief Checks if the given BasicBlock is in the interval.
     * @return true if the given BasicBlock is in the interval, false otherwise.
    */
    bool containsBlock(llvm::BasicBlock* bb) const noexcept;

     /**
     * @param bb: BasicBlock to be checked.
     * @brief Checks if the given BasicBlock is in the interval.
     * @return true if the given BasicBlock is in the interval, false otherwise.
    */
    bool containsBlock(const std::string& bbName) const noexcept;


    /**
     * @brief Removes all the elements from the interval. 
     */
    void clear() noexcept;

    /**
     * @brief Returns the first element of the interval.
     * @return the first element of the interval if it exists, an empty BB otherwise.
    */
    llvm::BasicBlock* getFirstBlock() const noexcept;
    /**
     * @brief Returns the last element of the interval.
     * @return the last element of the interval if it exists, an empty BB otherwise.
    */
    llvm::BasicBlock* getLastBlock() const noexcept;
    size_t size() const noexcept;
    bool isEmpty() const noexcept;
    std::vector<llvm::BasicBlock*> getBBlocks() const noexcept;
    std::vector<llvm::BasicBlock*> setBBlocks(std::vector<llvm::BasicBlock*> bbs);

    static std::vector<udm::Interval> intervals(llvm::Function& f, udm::FuncInfo& funcInfo);
private:
    std::vector<llvm::BasicBlock*> bBlocks;
};

} // namespace udm  

#endif