#include "settings/UdmSettings.h"

#include "logger/LoggerManager.h"

std::shared_ptr<settings::UdmSettings> settings::UdmSettings::m_instance;
std::once_flag settings::UdmSettings::m_flag;

settings::UdmSettings::UdmSettings()
{
    logger = logger::LoggerManager::getInstance()->getLogger("lifter");    
}

std::shared_ptr<settings::UdmSettings> settings::UdmSettings::getInstance() {
    std::call_once(m_flag, initInstance);
    return m_instance;
}

void settings::UdmSettings::initInstance() {
    m_instance = std::make_shared<settings::UdmSettings>(Foo());
};

void settings::UdmSettings::parseUdmSettings(const std::string& setting) {
    if (setting.length() < 2 || setting[0] != '-' || setting[1] != 'u') {
        logger->error("Invalid setting for udmSettings: {}", setting);
        return;
    }
    // create a copy of the setting string and remove the first two characters.
    std::string settingCopy = setting;
    settingCopy.erase(0, 2);
    // break after delimiter '=', if it doesn't exist log an error and return.
    size_t delimiterPos = settingCopy.find('=');
    if (delimiterPos == std::string::npos) {
        logger->error("Setting does not have a delimiter [=]: {}", setting);
        return;
    }
    // get the key and value from the setting string.
    std::string key = settingCopy.substr(0, delimiterPos);
    std::string value = settingCopy.substr(delimiterPos + 1);
}