#ifndef __FUNC_INFO_H__
#define __FUNC_INFO_H__

#include <iostream>
#include <unordered_map>
#include <memory>

#include "udm/BBInfo.h"

#include <llvm/IR/Function.h>

#include <spdlog/spdlog.h>


namespace udm {

class FuncInfo {
public:
    FuncInfo() = default;
    FuncInfo(llvm::Function& f);
    ~FuncInfo() = default;

    BBInfo getBBInfo(const std::string& bbName) const;
    bool addBBInfo(const std::string& bbName, const BBInfo& info);
    bool exists(const std::string& bbName) const;

    void print() const;
    std::string toString() const;
    BBInfo& operator[](const std::string& bbName);
private:
    std::unordered_map<std::string, BBInfo> bbInfo;
    std::shared_ptr<spdlog::logger> logger;

};

}   // namespace udm


#endif