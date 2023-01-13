#include "udm/FuncInfo.h"

bool udm::FuncInfo::addBBInfo(const std::string& bbName, const BBInfo& info)
{
    if(bbInfo.find(bbName) != bbInfo.end())
    {
        return false;
    }

    bbInfo[bbName] = info;
    return true;
}

udm::BBInfo udm::FuncInfo::getBBInfo(const std::string& bbName) const
{
    auto found = bbInfo.find(bbName);
    if(found == bbInfo.end())
    {
        return BBInfo();
    }

    return found->second;
}