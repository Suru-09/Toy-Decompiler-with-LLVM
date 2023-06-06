#include "settings/LifterSettings.h"

#include "logger/LoggerManager.h"

std::shared_ptr<settings::LifterSettings> settings::LifterSettings::m_instance;
std::once_flag settings::LifterSettings::m_flag;

settings::LifterSettings::LifterSettings() 
: m_serverUrl(""),
m_binaryPath("")
{
    logger = logger::LoggerManager::getInstance()->getLogger("lifter");
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

void settings::LifterSettings::parseLifterSettings(const std::string& setting) {
    // format of argv is: -lserverUrl=serverUrl -lbinaryPath=binaryPath and use switch case to parse it.
    // for now, just parse it manually.
    if (setting.length() < 2 || setting[0] != '-' || setting[1] != 'l') {
        logger->error("Invalid setting for lifterSettings: {}", setting);
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

    if (key == "serverUrl") {
        setServerUrl(value);
    } else if (key == "binaryPath") {
        setBinaryPath(value);
    } else {
        logger->error("Invalid key for lifterSettings: {}", key);
        return;
    }
}

