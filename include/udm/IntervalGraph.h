#ifndef __INTERVAL_GRAPH_H__
#define __INTERVAL_GRAPH_H__

#include <iostream>
#include <vector>

#include "udm/Interval.h"
#include "udm/BBInfo.h"

#include <llvm/IR/BasicBlock.h>

namespace udm {

class IntervalGraph {
public:
    IntervalGraph() = default;
    IntervalGraph(const std::vector<Interval>& intervals) : intervals(intervals) {}
    
    bool addInterval(Interval interval);
    bool containsInterval(Interval interval) const;

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

    bool isLowerBB(std::string firstBB, std::string secondBB);
    size_t getNumSuccessors(std::string bbName);
    size_t getNumPredecessors(std::string bbName);
    llvm::BasicBlock* getBB(std::string bbName);

    udm::BBInfo::LoopType getLoopType(std::pair<std::string, std::string> backEdge);

    void loopStructure(FuncInfo& funcInfo);
    std::vector<std::string> getAllNodesBetweenLatchAndHeader(std::pair<std::string, std::string> backEdge);
    bool isBBbeforeInterval(std::string& bbName, Interval interval);

    /**
     * @param f: Function to be analyzed.
     * @param funcInfo: FuncInfo object that contains the information about the function.
     * @brief Calculates the intervals of a function which helps to represent the control flow structures.
     * Also adds information about each BB in the funcInfo object.
     * @return a IntervalGraph object that represents the intervals of the function.
    */
    static IntervalGraph intervalsGraph(llvm::Function& f, FuncInfo& funcInfo);
private:
    std::vector<Interval> intervals;
};

}  // namespace udm

#endif
