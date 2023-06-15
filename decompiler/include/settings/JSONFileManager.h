#ifndef REVERSE_ENGINEERING_TOOL_JSONFILEMANAGER_H
#define REVERSE_ENGINEERING_TOOL_JSONFILEMANAGER_H

#include "FileManager.h"

#include <spdlog/spdlog.h>
#include <iostream>
#include <unordered_map>

namespace settings
{

class JSONFileManager : public FileManager {

public:
    explicit JSONFileManager();

    void writeToFile(const std::string& filename, const std::unordered_map<std::string, std::string>& settings) override;
    std::unordered_map<std::string, std::string> readFromFile(const std::string& filename) override;

private:
    std::shared_ptr<spdlog::logger> logger;
};

}   // end of namespace settings

#endif //REVERSE_ENGINEERING_TOOL_JSONFILEMANAGER_H
