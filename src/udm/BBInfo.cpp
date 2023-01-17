#include "udm/BBInfo.h"
#include "logger/LoggerManager.h"

#include <spdlog/spdlog.h>

udm::BBInfo::BBInfo() : 
isHeader(false),
isLoop(false),
isIfStatement(false),
loopType(LoopType::NONE),
followNode("")
{
    logger = logger::LoggerManager::getInstance()->getLogger("udm");
}

bool udm::BBInfo::getIsHeader() const
{
    return isHeader;
}

bool udm::BBInfo::getIsLoop() const
{
    return isLoop;
}

bool udm::BBInfo::getIsIfStatement() const
{
    return isIfStatement;
}

udm::BBInfo::LoopType udm::BBInfo::getLoopType() const
{
    return loopType;
}

void udm::BBInfo::setIsHeader(bool isHeader)
{
    this->isHeader = isHeader;
}

void udm::BBInfo::setIsLoop(bool isLoop)
{
    this->isLoop = isLoop;
}

void udm::BBInfo::setIsIfStatement(bool isIfStatement)
{
    this->isIfStatement = isIfStatement;
}

void udm::BBInfo::setLoopType(LoopType loopType)
{
    this->loopType = loopType;
}

void udm::BBInfo::print() const
{
    logger->info("isHeader: {}", isHeader);
    logger->info("isLoop: {}", isLoop);
    logger->info("isIfStatement: {}", isIfStatement);
    logger->info("loopType: {}", getLoopTypeString(static_cast<size_t>(loopType)));
    logger->info("followNode: {}", followNode.empty() ? "EMPTY" : followNode);
}

std::string udm::BBInfo::getLoopTypeString(size_t loopT)
{
    switch (loopT)
    {
        case 0:
            return "WHILE";
        case 1:
            return "DO_WHILE";
        case 2:
            return "INFINITE";
        case 3:
            return "NONE";
        default:
            return "ERROR";
    }
}

void udm::BBInfo::setFollowNode(std::string followNode)
{
    this->followNode = followNode;
}

std::string udm::BBInfo::getFollowNode() const
{
    return followNode;
}
