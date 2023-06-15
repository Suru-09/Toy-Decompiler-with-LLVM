#include "settings/UdmSettings.h"
#include "logger/LoggerManager.h"

#include <filesystem>
#include <fstream>

std::shared_ptr<settings::UdmSettings> settings::UdmSettings::m_instance;
std::once_flag settings::UdmSettings::m_flag;

settings::UdmSettings::UdmSettings()
{
    logger = logger::LoggerManager::getInstance()->getLogger("lifter");
    try
    {
        if(!std::filesystem::exists("../settings"))
        {
            logger->info("[UdmSettings::constructor] creating settings directory");
            std::filesystem::create_directory("../settings");
        }

        if(!std::filesystem::exists(m_fileName))
        {
            logger->info("[UdmSettings::constructor] creating UdmSettings file");
            std::ofstream file(m_fileName);
            if(!file.is_open()) {
                logger->error("[UdmSettings::constructor] failed to open a new UdmSettings file");
                return;
            }
            file.close();
        }
        else
        {
            logger->info("[UdmSettings::constructor] UdmSettings file already exists, reading from it");
            readSettingsFromFile();
        }
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        logger->error("[UdmSettings::constructor] failed to create settings directory: {}", e.what());
    }
    catch (const std::exception& e)
    {
        logger->error("[UdmSettings::constructor] fallback to std::exception to create settings directory: {}", e.what());
    }
}

std::shared_ptr<settings::UdmSettings> settings::UdmSettings::getInstance() {
    std::call_once(m_flag, initInstance);
    return m_instance;
}

void settings::UdmSettings::initInstance() {
    m_instance = std::make_shared<settings::UdmSettings>(Foo());
};

std::string settings::UdmSettings::getOptimizedIRPath() const {
    return m_optimizedIRPath;
}

void settings::UdmSettings::setOptimizedIRPath(const std::string& optimizedIRPath) {
    m_optimizedIRPath = optimizedIRPath;
}

void settings::UdmSettings::readSettingsFromFile() {
    // create unordered_map of settings
    auto settings = readFromFile(m_fileName);

    // set settings
    setOptimizedIRPath(settings["optimizedIRPath"]);
}

void settings::UdmSettings::writeSettingsToFile() {
    // create unordered_map of settings
    std::unordered_map<std::string, std::string> settings;
    settings["optimizedIRPath"] = getOptimizedIRPath();

    // write settings to file
    writeToFile(m_fileName, settings);
}
