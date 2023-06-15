#include "settings/JSONFileManager.h"
#include "logger/LoggerManager.h"

#include <fstream>
#include <filesystem>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

settings::JSONFileManager::JSONFileManager()
{
    logger = logger::LoggerManager::getInstance()->getLogger("lifter");
}

void settings::JSONFileManager::writeToFile(const std::string &filename,
                                            const std::unordered_map <std::string, std::string> &settings)
{
    try
    {
        // check if given file exists
        if (!std::filesystem::exists(filename))
        {
            logger->error("[JSONFileManager::writeToFile] file: {} does not exist", filename);
            return;
        }

        boost::property_tree::ptree propertyTree;
        for (const auto& setting : settings)
        {
            propertyTree.put(setting.first, setting.second);
        }

        boost::property_tree::write_json(filename, propertyTree);
    }
    catch(const boost::property_tree::json_parser_error&)
    {
        logger->error("[JSONFileManager::writeToFile] failed to parse json file: {}", filename);
        return;
    }
    catch (std::exception& e)
    {
        logger->error("[JSONFileManager::writeToFile] failed to write to file: {}", filename);
        return;
    }
}

std::unordered_map<std::string, std::string> settings::JSONFileManager::readFromFile(const std::string &filename)
{
    try
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            logger->error("[JSONFileManager::readFromFile] failed to open file: {}", filename);
            return {};
        }

        boost::property_tree::ptree propertyTree;
        boost::property_tree::read_json(file, propertyTree);
        std::unordered_map<std::string, std::string> settings;
        std::for_each(propertyTree.begin(), propertyTree.end(), [&settings, &propertyTree](auto& pair) {
            settings[pair.first] = propertyTree.get<std::string>(pair.first);
        });

        return settings;
    }
    catch(const boost::property_tree::json_parser_error&)
    {
        logger->error("[JSONFileManager::readFromFile] failed to parse json file: {}", filename);
        return {};
    }
    catch (const std::exception& e) {
        logger->error("[JSONFileManager::readFromFile] failed to read from file: {}", filename);
        return {};
    }
}
