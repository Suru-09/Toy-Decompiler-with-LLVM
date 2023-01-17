#include <iostream>
#include <memory>

#include "utils/LifterUtils.h"
#include "udm/UDM.h"
#include "logger/LoggerManager.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h" 
#include "spdlog/sinks/rotating_file_sink.h"


int main(int argc, char** argv) {
   std::string testing_file = "../testing_files/elfC/loops";
   std::shared_ptr<lifter::LifterContext> lifterCtx = utils::getLifterCtx(testing_file);

   //create an instance of logger manager(so that it is already initialized later).
   logger::LoggerManager* loggerManager = logger::LoggerManager::getInstance();

   if(!lifterCtx)
   {
      spdlog::critical("Invalid lifterContext created(nullptr)!");
      exit(1);
   }
   
   std::unique_ptr<udm::UDM> udm = std::make_unique<udm::UDM>(testing_file + ".ll");
   udm->execute();
   return 0;
}