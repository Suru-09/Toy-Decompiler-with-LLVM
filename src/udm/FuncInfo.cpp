#include "udm/FuncInfo.h"

#include <spdlog/spdlog.h>

udm::FuncInfo::FuncInfo(llvm::Function& f)
{
    for(auto& bb : f)
    {
        addBBInfo(bb.getName().str(), BBInfo());
    }
}

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

bool udm::FuncInfo::exists(const std::string& bbName) const
{
    return bbInfo.find(bbName) != bbInfo.end();
}

udm::BBInfo& udm::FuncInfo::operator[](const std::string& bbName)
{
    return bbInfo[bbName];
}

void udm::FuncInfo::print() const
{
    for(auto& bb : bbInfo)
    {
        spdlog::critical("Basic block with label: <{}>:", bb.first);
        bb.second.print();
    }
}