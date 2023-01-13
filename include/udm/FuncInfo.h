#ifndef __FUNC_INFO_H__
#define __FUNC_INFO_H__

#include <iostream>
#include <unordered_map>

#include "udm/BBInfo.h"


namespace udm {

class FuncInfo {
public:
    FuncInfo() = default;

    BBInfo getBBInfo(const std::string& bbName) const;
    bool addBBInfo(const std::string& bbName, const BBInfo& info);
private:
    std::unordered_map<std::string, BBInfo> bbInfo;
};

}   // namespace udm


#endif