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
    for(auto& bb : interval)
    {
        auto predecessors = utils::UdmUtils::getPredecessors(bb);
        for(auto& pred : predecessors)
        {
            if(isLowerBB(pred, bb->getName().str()))
            {
                return std::make_pair(bb->getName().str(), pred);
            }
        }
    }
    
    return std::make_pair("", "");
}

bool udm::IntervalGraph::isLowerBB(std::string firstBB, std::string secondBB)
{
    bool foundFirst = false;
    for(auto& interval : intervals)
    {
        for(auto& bb : interval)
        {            
            if(bb->getName().str() == secondBB)
            {
                if(!foundFirst)
                {
                    return true;
                }
            }
            
            if(bb->getName().str() == firstBB)
            {
                foundFirst = true;
            }
        }
    }
    return false;
}


void udm::IntervalGraph::loopStructure(udm::FuncInfo& funcInfo)
{
    for(auto& interval : intervals)
    { 
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

            if(funcInfo.exists(backEdge.first))
            {
                auto type = getLoopType(backEdge);
                spdlog::info("I am setting: <{}> with value: <{}>", backEdge.first, udm::BBInfo::getLoopTypeString(static_cast<size_t>(type)));
                funcInfo[backEdge.first].setLoopType(type);

                auto follow = getFollowNode(backEdge);
                spdlog::info("Follow node for backedge: <{}> -> <{}> is: <{}>", backEdge.first, backEdge.second, follow);
                funcInfo[backEdge.first].setFollowNode(follow);
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
    bool startAdd = false;
    std::string stop = backEdge.first;
    std::vector<std::string> nodesBetweenLatchAndHeader;

    for(auto& interval : intervals)
    {
        for(auto& bb : interval)
        {
            if(bb->getName().str() == backEdge.second)
            {
                startAdd = true;
            }

            if(startAdd)
            {
                nodesBetweenLatchAndHeader.push_back(bb->getName().str());
            }

            if(bb->getName().str() == stop)
            {
                // for(auto& tf : nodesBetweenLatchAndHeader)
                // {
                //    spdlog::critical("Node between latch and header: <{}>", tf);
                // }
                return nodesBetweenLatchAndHeader;
            }
        }
    }
    return nodesBetweenLatchAndHeader;
}

size_t udm::IntervalGraph::getNumSuccessors(std::string bbName)
{
    size_t count = 0;
    for(auto& interval : intervals)
    {
        auto block = interval.getBlock(bbName);
        if(block != nullptr)
        {
            return utils::UdmUtils::getSuccessors(block).size();
        }
    }
    return count;
}

size_t udm::IntervalGraph::getNumPredecessors(std::string bbName)
{
    auto block = getBB(bbName);
    if(block != nullptr)
    {
        return utils::UdmUtils::getPredecessors(block).size();
    }
    return -1;
}

llvm::BasicBlock* udm::IntervalGraph::getBB(std::string bbName)
{
    for(auto& interval : intervals)
    {
        auto block = interval.getBlock(bbName);
        if(block != nullptr)
        {
            return block;
        }
    }
    return nullptr;
}

udm::BBInfo::LoopType udm::IntervalGraph::getLoopType(std::pair<std::string, std::string> backEdge)
{
    if(backEdge.first.empty())
    {
        return udm::BBInfo::LoopType::NONE;
    }

    auto nodesBetweenLatchAndHeader = getAllNodesBetweenLatchAndHeader(backEdge);
    size_t nodeTypeHeader = getNumSuccessors(backEdge.first); 
    size_t nodeTypeLatch = getNumSuccessors(backEdge.second);

    spdlog::critical("Node header: <{}>", nodeTypeHeader);
    spdlog::critical("Node latch: <{}>", nodeTypeLatch);

    if(nodeTypeHeader >= 2)
    {
        if(nodeTypeLatch >= 2)
        {   
            auto bb = getBB(backEdge.second);
            if(!bb)
            {
                spdlog::critical("BB is null");
                return udm::BBInfo::LoopType::NONE;
            }
            auto predecessors = utils::UdmUtils::getPredecessors(bb);
            for(auto& pred : predecessors)
            {
                if(std::find(nodesBetweenLatchAndHeader.begin(), nodesBetweenLatchAndHeader.end(), pred) != nodesBetweenLatchAndHeader.end())
                {
                    return udm::BBInfo::LoopType::DO_WHILE;
                }
                else
                {
                    return udm::BBInfo::LoopType::WHILE;
                }
            }
        }
        else
        {
            return udm::BBInfo::LoopType::DO_WHILE;
        }
    }
    else
    {
        if(nodeTypeLatch >= 2)
        {
            return udm::BBInfo::LoopType::WHILE;
        }
        else
        {
            return udm::BBInfo::LoopType::INFINITE;
        }
    }
    

    return udm::BBInfo::LoopType::NONE;
}

std::string udm::IntervalGraph::getFollowNode(std::pair<std::string, std::string> backEdge)
{
    if(backEdge.first.empty())
    {
        return "";
    }

    auto nodesBetweenLatchAndHeader = getAllNodesBetweenLatchAndHeader(backEdge);
    size_t nodeTypeHeader = getNumSuccessors(backEdge.first); 
    size_t nodeTypeLatch = getNumSuccessors(backEdge.second);

    auto loopType = getLoopType(backEdge);
    auto latchSuccesors = utils::UdmUtils::getSuccessors(getBB(backEdge.second));
    auto headerSuccesors = utils::UdmUtils::getSuccessors(getBB(backEdge.first));

    spdlog::critical("Node header follow: <{}>", latchSuccesors.front());
    spdlog::critical("Node latch follow: <{}>", headerSuccesors.front());

    if(loopType == udm::BBInfo::LoopType::WHILE)
    {
        auto found = std::find(nodesBetweenLatchAndHeader.begin(), nodesBetweenLatchAndHeader.end(), latchSuccesors.front());
        bool condition = found == nodesBetweenLatchAndHeader.end() && latchSuccesors.front() != backEdge.first;
        if(!condition)
        {
            return latchSuccesors.back();
        }
        else
        {
            return latchSuccesors.front();
        }
    }
    else if(loopType == udm::BBInfo::LoopType::DO_WHILE)
    {
        auto found = std::find(nodesBetweenLatchAndHeader.begin(), nodesBetweenLatchAndHeader.end(), headerSuccesors.front());
        bool condition = found == nodesBetweenLatchAndHeader.end() && latchSuccesors.front() != backEdge.first;
        if(!condition)
        {
            return headerSuccesors.back();
        }
        else
        {
            return headerSuccesors.front();
        }
    }
    else if(loopType == udm::BBInfo::LoopType::INFINITE)
    {
        std::string follow = backEdge.first;
        for(auto& n: nodesBetweenLatchAndHeader)
        {
            auto foundLatch = std::find(nodesBetweenLatchAndHeader.begin(), nodesBetweenLatchAndHeader.end(), n);
            if(foundLatch == nodesBetweenLatchAndHeader.end())
            {
                continue;
            }

            if(std::find(nodesBetweenLatchAndHeader.begin(), nodesBetweenLatchAndHeader.end(), latchSuccesors.front()) == nodesBetweenLatchAndHeader.end()
                && isLowerBB(latchSuccesors.front(), follow) && follow != latchSuccesors.front())
            {
                follow = latchSuccesors.front();
            }
            else if(std::find(nodesBetweenLatchAndHeader.begin(), nodesBetweenLatchAndHeader.end(), latchSuccesors.back()) == nodesBetweenLatchAndHeader.end()
                && isLowerBB(latchSuccesors.back(), follow) && follow != latchSuccesors.back())
            {
                follow = latchSuccesors.back();
            }
        }
        if(follow != backEdge.first)
        {
            return follow;
        }
    }
    return "";
}