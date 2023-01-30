#ifndef _CODE_GENERATION_H_
#define _CODE_GENERATION_H_

#include <iostream>
#include <unordered_map>
#include <memory>

#include "udm/FuncInfo.h"

#include "spdlog/spdlog.h"

namespace codeGen {

class CodeGeneration {
public:
    CodeGeneration(const std::string& irFile, std::unordered_map<std::string, udm::FuncInfo> fnInfoMap);
    ~CodeGeneration() = default;

    void generate();
private:
    std::string irFile;
    std::unordered_map<std::string, udm::FuncInfo> funcInfoMap;
    std::shared_ptr<spdlog::logger> logger;
};

}   // namespace codeGen

#endif