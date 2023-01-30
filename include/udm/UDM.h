#ifndef _CFG__H
#define _CFG__H

#include <iostream>
#include <memory>
#include <unordered_map>

#include <llvm/IR/Function.h>

#include <spdlog/spdlog.h>

#include "udm/FuncInfo.h"

namespace udm
{

class UDM {
public:
    UDM() = delete;
    UDM(const std::string& IRFile);
    void execute();
    void printLoops(llvm::Function& f);
    std::unordered_map<std::string, udm::FuncInfo>& getFuncInfoMap();
private:
    std::string irFile;
    std::unordered_map<std::string, udm::FuncInfo> funcInfoMap;
    std::shared_ptr<spdlog::logger> logger;
};
    
} // namespace udm



#endif