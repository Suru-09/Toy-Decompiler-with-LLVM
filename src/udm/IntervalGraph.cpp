#include "udm/IntervalGraph.h"

#include "utils/UdmUtils.h"

#include <iostream>
#include <vector>

#include <llvm/IR/CFG.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/ADT/PostOrderIterator.h>

#include <spdlog/spdlog.h>

bool udm::IntervalGraph::addInterval(Interval interval)
{
    auto found = std::find_if(intervals.begin(), intervals.end(), [&interval](Interval i) {
        return i.getFirstBlock()->getName() == interval.getFirstBlock()->getName();
    });

    if(found != intervals.end())
    {
        return false;
    }

    intervals.push_back(interval);
    return true;
}

bool udm::IntervalGraph::containsInterval(Interval interval) const
{
    auto found = std::find_if(intervals.begin(), intervals.end(), [&interval](Interval i) {
        return i == interval;
    });

    if(found == intervals.end())
    {
        return false;
    }

    return true;
}

udm::IntervalGraph::iterator udm::IntervalGraph::begin() noexcept
{
    return intervals.begin();
}

udm::IntervalGraph::const_iterator udm::IntervalGraph::begin() const noexcept
{
    return intervals.begin();
}

udm::IntervalGraph::const_iterator udm::IntervalGraph::cbegin() const noexcept
{
    return intervals.cbegin();
}

udm::IntervalGraph::reverse_iterator udm::IntervalGraph::rbegin() noexcept
{
    return intervals.rbegin();
}

udm::IntervalGraph::const_reverse_iterator udm::IntervalGraph::rbegin() const noexcept
{
    return intervals.rbegin();
}

udm::IntervalGraph::const_reverse_iterator udm::IntervalGraph::crbegin() const noexcept
{
    return intervals.crbegin();
}

udm::IntervalGraph::iterator udm::IntervalGraph::end() noexcept
{
    return intervals.end();
}

udm::IntervalGraph::const_iterator udm::IntervalGraph::end() const noexcept
{
    return intervals.end();
}

udm::IntervalGraph::const_iterator udm::IntervalGraph::cend() const noexcept
{
    return intervals.cend();
}

udm::IntervalGraph::reverse_iterator udm::IntervalGraph::rend() noexcept
{
    return intervals.rend();
}

udm::IntervalGraph::const_reverse_iterator udm::IntervalGraph::rend() const noexcept
{
    return intervals.rend();
}

udm::IntervalGraph::const_reverse_iterator udm::IntervalGraph::crend() const noexcept
{
    return intervals.crend();
}

size_t udm::IntervalGraph::size() const noexcept
{
    return intervals.size();
}

bool udm::IntervalGraph::empty() const noexcept
{
    return intervals.empty();
}

udm::Interval& udm::IntervalGraph::operator[](size_t index) noexcept
{
    return intervals[index];
}

const udm::Interval& udm::IntervalGraph::operator[](size_t index) const noexcept
{
    return intervals[index];
}

udm::IntervalGraph udm::IntervalGraph::intervalsGraph(llvm::Function& f, udm::FuncInfo& funcInfo)
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
    for(auto& h: headers)
    {
        if(funcInfo.exists(h->getName().str()))
        {
            funcInfo[h->getName().str()].setIsHeader(true);
        }
    }
    return intervals;
}

std::pair<std::string, std::string> udm::IntervalGraph::backEdgeToPreviousInterval(udm::Interval interval)
{
    for(auto intv: intervals)
    {
        for(auto bb: interval)
        {
            spdlog::warn("Current BB: <{}>", bb->getName().str());
            auto succesors = utils::UdmUtils::getSuccessors(bb);
            for(auto& succ : succesors)
            {
                spdlog::warn("Sucessor: <{}>", succ);
                if(isUpperBB(succ, bb->getName().str()))
                {
                    return std::make_pair(succ, bb->getName().str());
                }
            }
        }

        if(intv == interval)
        {
            break;
        }
    }
    
    return std::make_pair("", "");
}

bool udm::IntervalGraph::isUpperBB(std::string firstBB, std::string secondBB)
{
    bool foundFirst = false;
    for(auto& interval : intervals)
    {
        for(auto& bb : interval)
        {
            spdlog::warn("Current ISUPPERBB: <{}>", bb->getName().str());
            if(bb->getName().str() == firstBB)
            {
                foundFirst = true;
            }
            if(bb->getName().str() == secondBB)
            {
                if(foundFirst)
                {
                    return true;
                }
            }
        }
    }
    return false;
}


void udm::IntervalGraph::loopStructure(udm::FuncInfo& funcInfo)
{
    for(auto& interval : intervals)
    {
        for(auto& bb : interval)
        {
            spdlog::warn("Current BB in LOOPSTRUCTURE: <{}>", bb->getName().str());
        }
        auto backEdge = backEdgeToPreviousInterval(interval);
        spdlog::critical(
            "Backedge: <{}> -> <{}>",
            backEdge.first,
            backEdge.second );

        if(!backEdge.first.empty())
        {
            for(auto& bbName: getAllNodesBetweenLatchAndHeader(backEdge))
            {
                if( funcInfo.exists(bbName) )
                {
                    funcInfo[bbName].setIsLoop(true);
                }
            }
        }
    }
}

bool udm::IntervalGraph::isBBbeforeInterval(std::string& bbName, udm::Interval interval)
{
    int count = 0;
    bool result = false, startCount = false;
    for(auto& intv: intervals)
    {
        if(intv == interval)
        {
            break;
        }

        if(intv.containsBlock(bbName))
        {
            result = true;
            startCount = true;
        }

        if(startCount)
        {
            count++;
        }
        
    }
    return count > 1 ? false : result;
}

std::vector<std::string> udm::IntervalGraph::getAllNodesBetweenLatchAndHeader(std::pair<std::string, std::string> backEdge)
{
    bool start = false;
    std::string stop = backEdge.second;
    std::vector<std::string> nodesBetweenLatchAndHeader;

    for(auto& interval : intervals)
    {
        if(interval.containsBlock(backEdge.first))
        {
            start = true;
        }
        if(start)
        {
            for(auto& bb : interval)
            {
                nodesBetweenLatchAndHeader.push_back(bb->getName().str());
                if(bb->getName().str() == stop)
                {
                    start = false;
                    return nodesBetweenLatchAndHeader;
                }
                
            }
        }
    }
    return nodesBetweenLatchAndHeader;
}