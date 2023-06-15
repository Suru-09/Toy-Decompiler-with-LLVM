#include "frontendQT/MainWindowQT.h"
#include "frontendQT/FileSelectorQT.h"
#include "frontendQT/FileViewerQT.h"

#include "utils/LifterUtils.h"
#include "logger/LoggerManager.h"
#include "udm/UDM.h"
#include "codeGen/CodeGeneration.h"
#include "settings/LifterSettings.h"
#include "settings/UdmSettings.h"
#include "settings/CodegenSettings.h"

#include <iostream>
#include <memory>
#include <future>
#include <thread>

#include <curl/curl.h>


frontend::MainWindowQT::MainWindowQT(QMainWindow *parent)
: QMainWindow(parent)
{
    // resize screen to 75% of the primary screen size.
    QScreen *primaryScreen = QApplication::primaryScreen();
    QRect screenGeometry = primaryScreen->geometry();
    int desiredWidth = screenGeometry.width() * 0.75;
    int desiredHeight = screenGeometry.height() * 0.75;
    resize(desiredWidth, desiredHeight);

    // create the main layout
    auto dropArea = new frontend::FileSelectorQT(this);
    setCentralWidget(dropArea);

    connect(dropArea, &frontend::FileSelectorQT::selectedFile, this, &frontend::MainWindowQT::onFileReceived);
}

bool frontend::MainWindowQT::decompileFiles(const QString &binPath) {
    curl_global_init(CURL_GLOBAL_ALL);

    // creating all the singletons first thing.
    logger::LoggerManager* loggerManager = logger::LoggerManager::getInstance();
    std::shared_ptr<settings::LifterSettings> lifterSettings = settings::LifterSettings::getInstance();
    std::shared_ptr<settings::UdmSettings> udmSettings = settings::UdmSettings::getInstance();
    std::shared_ptr<settings::CodegenSettings> codegenSettings = settings::CodegenSettings::getInstance();

    utils::cleanDownloadedFiles(5);

    lifterSettings->readSettingsFromFile();
    lifterSettings->setBinaryPath(binPath.toStdString());
    lifterSettings->writeSettingsToFile();

    const std::string& binaryName = lifterSettings->getBinaryName();
    const std::string& irFile = "../downloads/" + binaryName + ".ll";
    const std::string& optimizedIRFile = irFile.size() > 2 ? irFile.substr(0, irFile.size() - 3) + "_optimized.ll" : irFile;
    udmSettings->readSettingsFromFile();
    udmSettings->setOptimizedIRPath(optimizedIRFile);
    udmSettings->writeSettingsToFile();

    codegenSettings->readSettingsFromFile();

    std::shared_ptr<lifter::LifterContext> lifterCtx = utils::getLifterCtx();
    if(!lifterCtx)
    {
        spdlog::critical("Invalid lifterContext created(nullptr)!");
        return false;
    }
    lifterCtx->executeStrategy();

    std::unique_ptr<udm::UDM> udm = std::make_unique<udm::UDM>(irFile);
    udm->execute();

    auto funcInfoMap = udm->getFuncInfoMap();

    std::unique_ptr<codeGen::CodeGeneration> codeGen =
            std::make_unique<codeGen::CodeGeneration>(optimizedIRFile, funcInfoMap);
    codeGen->generate();

    // cleanup libcurl
    curl_global_cleanup();

    return true;
}

void frontend::MainWindowQT::onFileReceived(const QString &filePath) {
    // decompile file given the binaryPath
    m_isDecompiled = decompileFiles(filePath);
    const QString& outputPath = QString::fromStdString(settings::CodegenSettings::getInstance()->getFinalOutputFilePath());

    auto fileViewer = new frontend::FileViewerQT(this, outputPath);
    setCentralWidget(fileViewer);
}





