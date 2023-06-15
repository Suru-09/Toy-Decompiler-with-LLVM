#include "settings/LifterSettings.h"
#include "logger/LoggerManager.h"

#include <filesystem>
#include <fstream>


std::shared_ptr<settings::LifterSettings> settings::LifterSettings::m_instance;
std::once_flag settings::LifterSettings::m_flag;

settings::LifterSettings::LifterSettings() 
: m_serverUrl(""),
m_binaryPath("")
{
    logger = logger::LoggerManager::getInstance()->getLogger("lifter");
    try
    {
        if(!std::filesystem::exists("../settings"))
        {
            logger->info("[LifterSettings::constructor] creating settings directory");
            std::filesystem::create_directory("../settings");
        }

        if(!std::filesystem::exists(m_fileName))
        {
            logger->info("[LifterSettings::constructor] creating LifterSettings file");
            std::ofstream file(m_fileName);
            if(!file.is_open()) {
                logger->error("[LifterSettings::constructor] failed to open a new LifterSettings file");
                return;
            }
            file.close();
        }
        else
        {
            logger->info("[LifterSettings::constructor] LifterSettings file already exists, reading from it");
            readSettingsFromFile();
        }
    }
    catch(std::filesystem::filesystem_error& e)
    {
        logger->error("[LifterSettings::constructor] failed to create settings directory");
        return;
    }
    catch(std::exception& e)
    {
        logger->error("[LifterSettings::constructor] fallback to std::exception to create settings directory");
        return;
    }

}

std::shared_ptr<settings::LifterSettings> settings::LifterSettings::getInstance() {
    std::call_once(m_flag, initInstance);
    return m_instance;
}

void settings::LifterSettings::initInstance() {
    m_instance = std::make_shared<settings::LifterSettings>(Foo());
};

std::string settings::LifterSettings::getServerUrl() const {
    return m_serverUrl;
}

void settings::LifterSettings::setServerUrl(const std::string& serverUrl) {
    m_serverUrl = serverUrl;
}

std::string settings::LifterSettings::getBinaryPath() const {
    return m_binaryPath;
}

void settings::LifterSettings::setBinaryPath(const std::string& binaryPath) {
    m_binaryPath = binaryPath;
}

void settings::LifterSettings::writeSettingsToFile() {
    // create unordered_map of settings
    std::unordered_map<std::string, std::string> settings;
    settings["serverUrl"] = getServerUrl();
    settings["binaryPath"] = getBinaryPath();

    writeToFile(m_fileName, settings);
}

void settings::LifterSettings::readSettingsFromFile() {
    // create unordered_map of settings
    auto settings = readFromFile(m_fileName);

    // set settings
    setServerUrl(settings["serverUrl"]);
    setBinaryPath(settings["binaryPath"]);
}

std::string settings::LifterSettings::getBinaryName() const {
    if(m_binaryPath.empty())
        return "";
    
    auto pos = m_binaryPath.find_last_of("/\\");
    if(pos == std::string::npos)
        return m_binaryPath;
    else
        return m_binaryPath.substr(pos + 1);
}



