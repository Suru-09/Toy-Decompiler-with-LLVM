#include "udm/BBInfo.h"

udm::BBInfo::BBInfo() : 
isHeader(false),
isLoop(false),
isIfStatement(false) {}

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

