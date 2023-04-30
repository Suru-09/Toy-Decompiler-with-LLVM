#include "settings/CodegenSettings.h"

#include "logger/LoggerManager.h"

std::shared_ptr<settings::CodegenSettings> settings::CodegenSettings::m_instance;
std::once_flag settings::CodegenSettings::m_flag;

settings::CodegenSettings::CodegenSettings()
{
    logger = logger::LoggerManager::getInstance()->getLogger("lifter");    
}

std::shared_ptr<settings::CodegenSettings> settings::CodegenSettings::getInstance() {
    std::call_once(m_flag, initInstance);
    return m_instance;
}

void settings::CodegenSettings::initInstance() {
    m_instance = std::make_shared<settings::CodegenSettings>(Foo());
};

void settings::CodegenSettings::parseCodegenSettings(const std::string& setting) {
    if (setting.length() < 2 || setting[0] != '-' || setting[1] != 'c') {
        logger->error("Invalid setting for codegenSettings: {}", setting);
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

