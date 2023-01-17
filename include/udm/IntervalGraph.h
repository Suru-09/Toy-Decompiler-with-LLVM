#ifndef __INTERVAL_GRAPH_H__
#define __INTERVAL_GRAPH_H__

#include <iostream>
#include <vector>
#include <memory>

#include "udm/Interval.h"
#include "udm/BBInfo.h"

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Dominators.h>
#include "llvm/Analysis/PostDominators.h"

#include <spdlog/spdlog.h>

namespace udm {

class IntervalGraph {
public:
    IntervalGraph() = delete;
    IntervalGraph(llvm::PostDominatorTree& dt);
    
    bool addInterval(Interval interval);
    bool containsInterval(Interval interval) const;
    void setIntervals(const std::vector<Interval>& intervals);

    // Aliases for iterators
    using iterator = std::vector<Interval>::iterator;
    using reverse_iterator = std::vector<Interval>::reverse_iterator;
    using const_iterator = std::vector<Interval>::const_iterator;
    using const_reverse_iterator = std::vector<Interval>::const_reverse_iterator;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator crbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crend() const noexcept;

    // Interval Graph size methods
    size_t size() const noexcept;
    bool empty() const noexcept;

    // Interval Graph access methods
    Interval& operator[](size_t index) noexcept;
    const Interval& operator[](size_t index) const noexcept;

    /**
     * @param interval: Interval to be searched.
     * @brief Searched for a back edge to the previous interval.
     * @return a pair<string, string>, where first string is the header and the second string 
     * is the latch of the previous interval.
    */
    std::pair<std::string, std::string> backEdgeToPreviousInterval(Interval interval);

    bool isLowerOrEqBB(std::string firstBB, std::string secondBB);
    size_t getNumSuccessors(std::string bbName);
    size_t getNumPredecessors(std::string bbName);
    llvm::BasicBlock* getBB(std::string bbName);


    std::string getFollowNode(std::pair<std::string, std::string> backEdge);

    /**
     * @param backEdge: pair<string, string> where first string is the header and the second string 
     * is the latch of the previous interval.
     * @brief Calculates the loop type of the back edge.
     * @return udm::BBInfo::LoopType(DO_WHILE, WHILE, INFINITE, NONE).
    */
    udm::BBInfo::LoopType getLoopType(std::pair<std::string, std::string> backEdge);

    /**
     * @param funcInfo: FuncInfo object that contains the information about the function.
     * @brief Calculates the control flow structures of the function and completes information
     * about the function such as follow node and loop type.
    */
    void loopStructure(FuncInfo& funcInfo);

    void setBlocksInLoop(const std::vector<std::string>& nodesInLoop, FuncInfo& funcInfo);
    void setBlockLoopType(const std::pair<std::string, std::string>& backEdge, FuncInfo& funcInfo);
    void setFollowBlock(const std::pair<std::string, std::string>& backEdge, FuncInfo& funcInfo);

    /**
     * @param bb : Basic block to be searched.
     * @brief Finds the immediate dominator of a basic block.
     * @return the immediate dominator of the basic block.
    */
    llvm::BasicBlock* findImediateDominator(llvm::BasicBlock* bb);


    /**
     * @param funcInfo: FuncInfo object that contains the information about the function.
     * @brief Calculates the control flow structures of the function and completes information
     * about the function such as the follow node for two way conditional branches.
    */
    void twoWayConditionalBranch(FuncInfo& funcInfo);


    /**
     * @param backEdge: pair<string, string> where first string is the header and the second string 
     * is the latch of the previous interval.
     * @brief Calculates the nodes between the latch and the header of the back edge.
     * @return a vector of strings that contains the names of the nodes between the latch and the header.
    */
    std::vector<std::string> getAllNodesBetweenLatchAndHeader(std::pair<std::string, std::string> backEdge);


    /**
     * @param bbName: Name of the basic block.
     * @param interval: Interval to be searched.
     * @brief Checks if the basic block is before the interval.
     * @return true if the basic block is before the interval, false otherwise.
    */
    bool isBBbeforeInterval(std::string& bbName, Interval interval);

    /**
     * @param f: Function to be analyzed.
     * @param funcInfo: FuncInfo object that contains the information about the function.
     * @brief Calculates the intervals of a function which helps to represent the control flow structures.
     * Also adds information about each BB in the funcInfo object.
     * @return a IntervalGraph object that represents the intervals of the function.
    */
    std::vector<Interval> intervalsGraph(llvm::Function& f, FuncInfo& funcInfo);
private:
    std::vector<Interval> intervals;
    llvm::PostDominatorTree& dt;
    std::shared_ptr<spdlog::logger> logger;

};

}  // namespace udm

#endif
