#ifndef REVERSE_ENGINEERING_TOOL_BRACKETMANAGER_H
#define REVERSE_ENGINEERING_TOOL_BRACKETMANAGER_H

#include <string>
#include <map>
#include <memory>
#include <spdlog/spdlog.h>

#include "udm/BBInfo.h"
#include "udm/FuncInfo.h"

namespace codeGen {

class BracketManager {
public:
    BracketManager() = default;
    ~BracketManager() = default;

    static udm::BBInfo::LoopType isLoop(const udm::BBInfo& bbInfo);
    static bool isConditional(const udm::BBInfo& bbInfo);

    static void addBracket(const std::string& bbName, const udm::FuncInfo& funcInfo);

    static bool shouldCloseConditional(const std::string& bbName, const udm::FuncInfo& funcInfo);
    static bool shouldCloseLoop(const std::string& bbName, const udm::FuncInfo& funcInfo);

private:
    static std::map<std::pair<std::string, std::string> , unsigned int> bracketMap;
    static std::shared_ptr<spdlog::logger> logger;
};

};


#endif //REVERSE_ENGINEERING_TOOL_BRACKETMANAGER_H
