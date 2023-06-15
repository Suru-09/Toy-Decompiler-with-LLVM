#include <iostream>
#include <memory>

#include "utils/LifterUtils.h"
#include "udm/UDM.h"
#include "logger/LoggerManager.h"
#include "codeGen/CodeGeneration.h"

#include "settings/LifterSettings.h"
#include "settings/UdmSettings.h"
#include "settings/CodegenSettings.h"

#include <curl/curl.h>

#include "frontendQT/MainWindowQT.h"

int main(int argc, char** argv) {
   // initialize libcurl
   curl_global_init(CURL_GLOBAL_ALL);
   
   // creating all the singletons first thing.
   logger::LoggerManager* loggerManager = logger::LoggerManager::getInstance();
   std::shared_ptr<settings::LifterSettings> lifterSettings = settings::LifterSettings::getInstance();
   std::shared_ptr<settings::UdmSettings> udmSettings = settings::UdmSettings::getInstance();
   std::shared_ptr<settings::CodegenSettings> codegenSettings = settings::CodegenSettings::getInstance();

   std::string testing_file = "../testing_files/elfC/bsearch";
   lifterSettings->setBinaryPath(testing_file);
   lifterSettings->setServerUrl("http://145.14.158.175:29200");

   lifterSettings->writeSettingsToFile();

   codegenSettings->setOutputFilePath("../output");
   
   std::shared_ptr<lifter::LifterContext> lifterCtx = utils::getLifterCtx();
   if(!lifterCtx)
   {
      spdlog::critical("Invalid lifterContext created(nullptr)!");
      exit(1);
   }
   lifterCtx->executeStrategy();

   std::string irFile = testing_file + ".ll";
   std::unique_ptr<udm::UDM> udm = std::make_unique<udm::UDM>(irFile);
   udm->execute();

   auto funcInfoMap = udm->getFuncInfoMap();
   
   std::string optimizedIRFile = irFile.size() > 2 ? irFile.substr(0, irFile.size() - 3) + "_optimized.ll" : irFile;
   std::unique_ptr<codeGen::CodeGeneration> codeGen = 
      std::make_unique<codeGen::CodeGeneration>(optimizedIRFile, funcInfoMap);
   codeGen->generate();

   // cleanup libcurl
   curl_global_cleanup();

    QApplication app(argc, argv);

    const std::string& outputFilePath = codegenSettings->getFinalOutputFilePath();
    frontend::MainWindowQT mainWindow;
    mainWindow.loadDecompiledFiles(QString::fromStdString(outputFilePath));
    mainWindow.show();

    return app.exec();
}
