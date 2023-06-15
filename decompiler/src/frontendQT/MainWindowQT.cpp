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

#include <memory>
#include <thread>

#include <curl/curl.h>
#include <QApplication>

frontend::MainWindowQT::MainWindowQT(QMainWindow *parent)
: QMainWindow(parent)
{
    loadFileSelector();
}

void frontend::MainWindowQT::resizeScreen(const double &sizePercent) {
    QScreen *primaryScreen = QApplication::primaryScreen();
    QRect screenGeometry = primaryScreen->geometry();
    int desiredWidth = screenGeometry.width() * sizePercent;
    int desiredHeight = screenGeometry.height() * sizePercent;
    resize(desiredWidth, desiredHeight);

    // center the window
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();
    int x = (screenWidth - desiredWidth) / 2;
    int y = (screenHeight - desiredHeight) / 2;
    move(x, y);
}

frontend::FileSelectorQT *frontend::MainWindowQT::loadFileSelector() {
    // make sure the window is a reasonable size
    resizeScreen(0.25);
    auto fileSelector = new FileSelectorQT(this);
    setCentralWidget(fileSelector);

    connect(fileSelector, &FileSelectorQT::selectedFile, this, &MainWindowQT::onFileReceived);
    return fileSelector;
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
    // increase the size of the window
    resizeScreen(0.75);

    // decompile file given the binaryPath
    m_isDecompiled = decompileFiles(filePath);
    const QString& outputPath = QString::fromStdString(settings::CodegenSettings::getInstance()->getFinalOutputFilePath());

    auto fileViewer = new frontend::FileViewerQT(this, outputPath);
    setCentralWidget(fileViewer);

    connect(fileViewer, &frontend::FileViewerQT::backButtonClicked, this, &frontend::MainWindowQT::onReturnButtonClicked);
}

void frontend::MainWindowQT::onReturnButtonClicked() {
    auto fileSelector = loadFileSelector();
    setCentralWidget(fileSelector);

    connect(fileSelector, &frontend::FileSelectorQT::selectedFile, this, &frontend::MainWindowQT::onFileReceived);
}






