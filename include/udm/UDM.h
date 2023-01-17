#ifndef _CFG__H
#define _CFG__H

#include <iostream>
#include <memory>

#include <llvm/IR/Function.h>

#include <spdlog/spdlog.h>

namespace udm
{

class UDM {
public:
    UDM() = delete;
    UDM(const std::string& IRFile);
    void execute();
    void printLoops(llvm::Function& f);
private:
    std::string irFile;
    std::shared_ptr<spdlog::logger> logger;
};
    
} // namespace udm



#endif