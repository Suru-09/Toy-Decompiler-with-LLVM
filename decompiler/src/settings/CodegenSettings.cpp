#include "settings/CodegenSettings.h"

#include "logger/LoggerManager.h"
#include "settings/LifterSettings.h"

#include <filesystem>
#include <fstream>

std::shared_ptr<settings::CodegenSettings> settings::CodegenSettings::m_instance;
std::once_flag settings::CodegenSettings::m_flag;

settings::CodegenSettings::CodegenSettings()
{
    logger = logger::LoggerManager::getInstance()->getLogger("lifter");

    try {
        if (!std::filesystem::exists("../settings")) {
            logger->info("[CodegenSettings::constructor] creating settings directory");
            std::filesystem::create_directory("../settings");
        }

        if(!std::filesystem::exists(m_fileName))
        {
            logger->info("[CodegenSettings::constructor] creating CodegenSettings file");
            std::ofstream file(m_fileName);
            if(!file.is_open()) {
                logger->error("[CodegenSettings::constructor] failed to open a new CodegenSettings file");
                return;
            }
            file.close();
        }
        else
        {
            logger->info("[CodegenSettings::constructor] CodegenSettings file already exists, reading from it");
            readSettingsFromFile();
        }
    }
    catch (std::filesystem::filesystem_error& e) {
        logger->error("[CodegenSettings::constructor] failed to create settings directory");
        return;
    }
    catch (std::exception& e) {
        logger->error("[CodegenSettings::constructor] fallback to std::exception to create settings directory");
        return;
    }
}

std::shared_ptr<settings::CodegenSettings> settings::CodegenSettings::getInstance() {
    std::call_once(m_flag, initInstance);
    return m_instance;
}

void settings::CodegenSettings::initInstance() {
    m_instance = std::make_shared<settings::CodegenSettings>(Foo());
};

const std::string &settings::CodegenSettings::getOutputFilePath() const {
    return m_outputFilePath;
}

void settings::CodegenSettings::setOutputFilePath(const std::string &outputFilePath) {
    m_outputFilePath = outputFilePath;
}

std::string settings::CodegenSettings::getFinalOutputFilePath() const {
    // add the folder path to the output file name.
    std::string binaryPath = settings::LifterSettings::getInstance()->getBinaryPath();
    // get binary name from the binary path.
    std::string binaryName = binaryPath.substr(binaryPath.find_last_of("/\\") + 1);
    auto pos = binaryPath.find_last_of("/\\");
    if (pos == std::string::npos)
    {
        binaryName = binaryPath;
    }
    else
    {
        binaryName = binaryPath.substr(binaryPath.find_last_of("/\\") + 1);
    }

    auto finalOutputFilePath = m_outputFilePath + "/" + binaryName;
    try {
        if (!std::filesystem::exists(finalOutputFilePath))
        {
            std::filesystem::create_directory(finalOutputFilePath);
        }
    }
    catch (std::filesystem::filesystem_error& e) {
        logger->error("[CodegenSettings::getFinalOutputFilePath] Error creating directory: {}", e.what());
    }

    return finalOutputFilePath;
}

void settings::CodegenSettings::writeSettingsToFile() {
    std::unordered_map<std::string, std::string> settings;
    settings["outputFilePath"] = m_outputFilePath;
    // write settings to file
    writeToFile(m_fileName, settings);
}

void settings::CodegenSettings::readSettingsFromFile() {
    auto settings = readFromFile(m_fileName);

    // set settings, add more settings here
    m_outputFilePath = settings["outputFilePath"];
}

