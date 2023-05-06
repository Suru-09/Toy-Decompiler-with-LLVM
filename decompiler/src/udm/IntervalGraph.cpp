#include "udm/IntervalGraph.h"
#include "logger/LoggerManager.h"

#include "utils/UdmUtils.h"

#include <iostream>
#include <vector>

#include <llvm/IR/CFG.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/ADT/PostOrderIterator.h>

#include <spdlog/spdlog.h>

udm::IntervalGraph::IntervalGraph(llvm::PostDominatorTree& pdt)
:
dt(pdt)
{
    logger = logger::LoggerManager::getInstance()->getLogger("udm");
}

void udm::IntervalGraph::setIntervals(const std::vector<Interval>& intervals)
{
    this->intervals = intervals;
}

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

void udm::IntervalGraph::setHeadersOfIntervals(udm::Interval& headers, FuncInfo& funcInfo)
{
    for(const auto& h: headers)
    {
        if(funcInfo.exists(h->getName().str()))
        {
            funcInfo[h->getName().str()].setIsHeader(true);
        }
    }
}

std::vector<udm::Interval> udm::IntervalGraph::intervalsGraph(llvm::Function& f, udm::FuncInfo& funcInfo)
{
    llvm::ReversePostOrderTraversal<llvm::Function*> rpot(&f);
    udm::Interval headers;
    udm::Interval interval;
    std::vector<udm::Interval> intervals;

    for(auto& bb : rpot)
    {
        // the first basic block in a function is always a header
        if(headers.isEmpty())
        {
            headers.addBlock(bb);
        }
        interval.addBlock(bb);

        auto predecessors = utils::UdmUtils::getPredecessors(bb);
        logger->debug("Size of predecessors: <{}>", predecessors.size());
        if(interval.containsBlocks(predecessors))
        {
           interval.addBlock(bb);
           continue; 
        }

        headers.addBlock(bb);
        intervals.emplace_back(interval);
        interval.clear();
    }
    intervals.emplace_back(interval);
    
    //add info about headers in function information
    setHeadersOfIntervals(headers, funcInfo);

    return intervals;
}

std::pair<std::string, std::string> udm::IntervalGraph::backEdgeToPreviousInterval(udm::Interval interval)
{
    for(auto& bb : interval)
    {
        auto predecessors = utils::UdmUtils::getPredecessors(bb);
        for(auto& pred : predecessors)
        {
            if(isLowerOrEqBB(pred, bb->getName().str()))
            {
                return std::make_pair(bb->getName().str(), pred);
            }
        }
    }
    return std::make_pair("", "");
}

bool udm::IntervalGraph::isLowerOrEqBB(std::string firstBB, std::string secondBB)
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

void udm::IntervalGraph::setBlocksInLoop(const std::vector<std::string>& blocks, udm::FuncInfo& funcInfo)
{
    for(auto& bbName : blocks)
    {
        if(funcInfo.exists(bbName))
        {
            funcInfo[bbName].setIsLoop(true);
        }
    }
}

void udm::IntervalGraph::setBlockLoopType(const std::pair<std::string, std::string>& backEdge, udm::FuncInfo& funcInfo)
{
    if(funcInfo.exists(backEdge.first))
    {
        auto type = getLoopType(backEdge);
        logger->info("I am setting: <{}> with value: <{}>", backEdge.first, udm::BBInfo::getLoopTypeString(static_cast<size_t>(type)));
        funcInfo[backEdge.first].setLoopType(type);
        funcInfo[backEdge.first].setIsLoop(true);

    }
}

void udm::IntervalGraph::setFollowBlock(const std::pair<std::string, std::string>& backEdge, udm::FuncInfo& funcInfo)
{
    if(funcInfo.exists(backEdge.first))
    {
        auto follow = getFollowBlock(backEdge);
        logger->info("Follow node for backedge: <{}> -> <{}> is: <{}>", backEdge.first, backEdge.second, follow);
        funcInfo[backEdge.first].setFollowNode(follow);
    }
}

void udm::IntervalGraph::loopStructure(udm::FuncInfo& funcInfo)
{
    for(auto& interval : intervals)
    { 
        auto backEdge = backEdgeToPreviousInterval(interval);
        logger->critical(
            "Backedge: <{}> -> <{}>",
            backEdge.first,
            backEdge.second );

        if(backEdge.first.empty())
        {
            continue;
        }

        auto blocks = getBlocksBetweenLatchAndHeader(backEdge);
        setBlocksInLoop(blocks, funcInfo);

        logger->info("getBlocksBetweenLatchAndHeader size: {}", blocks.size());
        for(const auto& bbName : blocks)
        {
            logger->info("getBlocksBetweenLatchAndHeader: <{}>", bbName);
        }
        setBlockLoopType(backEdge, funcInfo);
        setFollowBlock(backEdge, funcInfo);          
    }
}

bool udm::IntervalGraph::isBBlockbeforeInterval(std::string& bbName, udm::Interval interval)
{
    for(const auto& intv: intervals)
    {
        if(intv == interval)
        {
            break;
        }

        if(intv.containsBlock(bbName))
        {
            return true;
        }
    }
    return false;
}

std::vector<std::string> udm::IntervalGraph::getBlocksBetweenLatchAndHeader(std::pair<std::string, std::string> backEdge)
{
    bool startAdd = false;
    std::string stop = backEdge.second;
    std::vector<std::string> nodesBetweenLatchAndHeader;

    if(backEdge.first == backEdge.second)
    {
        nodesBetweenLatchAndHeader.push_back(backEdge.first);
        return nodesBetweenLatchAndHeader;
    }

    for(auto& interval : intervals)
    {
        for(auto& bb : interval)
        {
            const auto& bbName = bb->getName().str();
            logger->info("getBlocksBetweenLatchAndHeader: <{}>", bbName);
            if(bbName == backEdge.first)
            {
                startAdd = true;
            }

            if(startAdd)
            {
                nodesBetweenLatchAndHeader.push_back(bb->getName().str());
            }

            if(bbName == stop)
            {
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

    const std::string preheader = "preheader";
    if ( backEdge.first.substr(backEdge.first.length() - preheader.length()) == preheader
        || backEdge.second.substr(backEdge.second.length() - preheader.length()) == preheader
        || ( backEdge.first == backEdge.second &&
            ( backEdge.first.find("ph") != std::string::npos || backEdge.second.find("ph") != std::string::npos )
        )

    )
    {
        return udm::BBInfo::LoopType::WHILE;
    }

    auto nBetweenLatchAndHeader = getBlocksBetweenLatchAndHeader(backEdge);
    size_t headerSuccessorsNum = getNumSuccessors(backEdge.first); 
    size_t latchSuccessorsNum = getNumSuccessors(backEdge.second);

    if(backEdge.first == backEdge.second)
    {
        std::vector<std::string> preds = utils::UdmUtils::getPredecessors(getBB(backEdge.first));
        logger->critical("[getLoopType] Node header: <{}>, preds size: <{}>", preds.front(), preds.size());
        auto found = std::find(preds.begin(), preds.end(), "preheader");
        if(found != preds.end())
        {
            return udm::BBInfo::LoopType::WHILE;
        }
        else
        {
            return udm::BBInfo::LoopType::DO_WHILE;
        }
    }

    logger->critical("[getLoopType] Node header: <{}>", headerSuccessorsNum);
    logger->critical("[getLoopType] Node latch: <{}>", latchSuccessorsNum);

    if(headerSuccessorsNum >= 2)
    {
        if(latchSuccessorsNum >= 2)
        {   
            auto bb = getBB(backEdge.second);
            if(!bb)
            {
                logger->critical("BB is null");
                return udm::BBInfo::LoopType::NONE;
            }

            auto predVector = utils::UdmUtils::getPredecessors(bb);
            auto firstPred = predVector.front();
            if(firstPred == "")
            {
                logger->critical("First pred is null");
                return udm::BBInfo::LoopType::NONE;
            }

            auto found = std::find(nBetweenLatchAndHeader.begin(), nBetweenLatchAndHeader.end(), firstPred);
            if(found != nBetweenLatchAndHeader.end())
            {
                return udm::BBInfo::LoopType::DO_WHILE;
            }
  
            return udm::BBInfo::LoopType::WHILE;
        }
        return udm::BBInfo::LoopType::DO_WHILE;
    }

    if(latchSuccessorsNum >= 2)
    {
        return udm::BBInfo::LoopType::WHILE;
    }

    return udm::BBInfo::LoopType::INFINITE;
}

std::string udm::IntervalGraph::getFollowBlock(const std::pair<std::string, std::string>& backEdge)
{   
    std::string header = backEdge.first;
    std::string latch = backEdge.second;

    if(header.empty())
    {
        return "";
    }

    auto nBetweenLatchAndHeader = getBlocksBetweenLatchAndHeader(backEdge);
    
    auto foundNode = [&nBetweenLatchAndHeader](const std::string& node)
    {
        auto found = std::find(nBetweenLatchAndHeader.begin(), nBetweenLatchAndHeader.end(), node);
        return found != nBetweenLatchAndHeader.end();
    };

    auto followNodeFirstSucc = [&](const std::vector<std::string>& successors)
    {
        bool foundFirstSucc = foundNode(successors.front()) && successors.front() != header;
        if(!foundFirstSucc)
        {
            return successors.back();
        }
        return successors.front();
    };

    auto latchSuccesors = utils::UdmUtils::getSuccessors(getBB(backEdge.second));
    auto headerSuccesors = utils::UdmUtils::getSuccessors(getBB(header));

    logger->critical("Node header follow: <{}>", latchSuccesors.front());
    logger->critical("Node latch follow: <{}>", headerSuccesors.front());

    auto loopType = getLoopType(backEdge);
    if(loopType == udm::BBInfo::LoopType::WHILE)
    {
        return followNodeFirstSucc(latchSuccesors);
    }
    else if(loopType == udm::BBInfo::LoopType::DO_WHILE)
    {
        return followNodeFirstSucc(headerSuccesors);
    }
    else if(loopType == udm::BBInfo::LoopType::INFINITE)
    {
        std::string follow = header;
        for(auto& n: nBetweenLatchAndHeader)
        {
            if(!foundNode(n))
            {
                continue;
            }

            auto followSuccInfinite = [&](const std::string& node)
            {
                auto found = foundNode(node);
                return found && follow != node && isLowerOrEqBB(node, follow);
            };

            if(followSuccInfinite(latchSuccesors.front()))
            {
                follow = latchSuccesors.front();
            }
            else if(followSuccInfinite(latchSuccesors.back()))
            {
                follow = latchSuccesors.back();
            }
        }
        
        if(follow != header)
        {
            return follow;
        }
    }
    return "";
}

llvm::BasicBlock* udm::IntervalGraph::findImediateDominator(llvm::BasicBlock* bb)
{
    auto node = dt.getNode(bb);
    return node && node->getIDom() ? node->getIDom()->getBlock() : nullptr;
}

void udm::IntervalGraph::twoWayConditionalBranch(udm::FuncInfo& funcInfo)
{
    std::vector<std::string> unresolved;
    for(auto intervIter = intervals.rbegin(); intervIter != intervals.rend(); ++intervIter)
    {   
        auto interval = *intervIter;
        for(auto bbIter = interval.rbegin(); bbIter != interval.rend(); ++ bbIter)
        {
            auto block = *bbIter;
            std::string bb = block->getName().str();
            logger->warn("BB: <{}>", bb);
            size_t bbOuterEdge = getNumSuccessors(bb);
            bool isHead = false;
            if(funcInfo.exists(bb))
            {
                isHead = funcInfo[bb].getIsHeader();
            }
            logger->warn("Outer edges: <{}>", bbOuterEdge);
            if( bbOuterEdge >= 2)
            {
                auto imedDom = findImediateDominator(block);
                logger->warn("is imedDom null?: <{}>", imedDom == nullptr);
                if(!imedDom)
                {
                    continue;
                }
                std::string imed = imedDom->getName().str();
                logger->warn("BB: <{}> imedDom: <{}>", bb, imed);
                logger->warn("Preds: <{}>", getNumPredecessors(imed));

                if(getNumPredecessors(imed) >= 2)
                {
                    funcInfo[bb].setFollowNode(imed);
                    for(const auto& notSolved: unresolved)
                    {
                        funcInfo[notSolved].setFollowNode(imed);
                    }
                }
                else
                {
                    unresolved.push_back(bb);
                }
            }
            
        }
    }
}