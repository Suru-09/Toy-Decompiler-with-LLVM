#include "logger/LoggerManager.h"

#include "spdlog/sinks/basic_file_sink.h" 

logger::LoggerManager* logger::LoggerManager::instance = nullptr;

logger::LoggerManager* logger::LoggerManager::getInstance()
{
    if(instance == nullptr)
    {
        instance = new LoggerManager();
    }
    return instance;
}

std::shared_ptr<spdlog::logger> logger::LoggerManager::getLogger(const std::string& name)
{
    auto found = loggers.find(name);
    if(found == loggers.end())
    {
        try
        {
            // third argument is to truncate file.
            loggers[name] = spdlog::basic_logger_mt(name, "../logs/" + name + ".log", true);
            return loggers[name];
        }
        catch(const spdlog::spdlog_ex& ex)
        {
            spdlog::critical("Log init failed: {}", ex.what());
            exit(1);
        }
    }
    return found->second;
}

