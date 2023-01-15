#ifndef __FUNC_INFO_H__
#define __FUNC_INFO_H__

#include <iostream>
#include <unordered_map>

#include "udm/BBInfo.h"

#include <llvm/IR/Function.h>


namespace udm {

class FuncInfo {
public:
    FuncInfo(llvm::Function& f);

    BBInfo getBBInfo(const std::string& bbName) const;
    bool addBBInfo(const std::string& bbName, const BBInfo& info);
    bool exists(const std::string& bbName) const;

    void print() const;
    BBInfo& operator[](const std::string& bbName);
private:
    std::unordered_map<std::string, BBInfo> bbInfo;
};

}   // namespace udm


#endif