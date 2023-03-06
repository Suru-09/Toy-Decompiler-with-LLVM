#ifndef _LOGGER_MANAGER_H_
#define _LOGGER_MANAGER_H_

#include <iostream>
#include <memory>
#include <unordered_map>

#include "spdlog/spdlog.h"

namespace logger {

class LoggerManager {
public:
    static LoggerManager* getInstance();
    /**
     * @param name The name of the logger.
     * @brief Get the Logger object and create it if it doesn't exist.
     * @return std::shared_ptr<spdlog::logger>.
    */
    std::shared_ptr<spdlog::logger> getLogger(const std::string& name);
private:
    static LoggerManager* instance;
    std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> loggers;
};

} // namespace logger

#endif