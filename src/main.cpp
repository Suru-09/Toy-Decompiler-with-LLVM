#include <iostream>
#include <memory>

#include "utils/LifterUtils.h"
#include "udm/UDM.h"


#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h" 
#include "spdlog/sinks/rotating_file_sink.h"


int main(int argc, char** argv) {
   std::string testing_file = "../testing_files/elfC/test";

   std::shared_ptr<lifter::LifterContext> lifterCtx = utils::getLifterCtx(testing_file);

   if(!lifterCtx)
   {
      spdlog::critical("Invalid lifterContext created(nullptr)!");
      exit(1);
   }
   
   // TODO: Modify the way of logging
   try
   {
      auto udmLogger = spdlog::rotating_logger_mt("udm", "../logs/udm.log", 1048576 * 5, 3);
      auto lifterLogger = spdlog::rotating_logger_mt("lifter", "../logs/lifter.log", 1048576 * 5, 3);
      auto codeGenLogger = spdlog::rotating_logger_mt("codeGen", "../logs/codeGen.log", 1048576 * 5, 3);
   }
   catch(const spdlog::spdlog_ex& ex)
   {
      std::cout << "Log init failed: " << ex.what() << std::endl;
   }

   std::unique_ptr<udm::UDM> udm = std::make_unique<udm::UDM>(testing_file + ".ll");
   udm->execute();
   return 0;
}