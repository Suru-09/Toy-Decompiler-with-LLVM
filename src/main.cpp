#include <iostream>
#include <memory>

#include "utils/LifterUtils.h"
#include "udm/UDM.h"
#include "spdlog/spdlog.h"


int main(int argc, char** argv) {
   std::string testing_file = "../testing_files/elfC/test";

   std::shared_ptr<lifter::LifterContext> lifterCtx = utils::getLifterCtx(testing_file);

   if(!lifterCtx)
   {
      spdlog::critical("Invalid lifterContext created(nullptr)!");
      exit(1);
   }
      
   //lifterCtx->executeStrategy();
   std::unique_ptr<udm::UDM> udm = std::make_unique<udm::UDM>(testing_file + ".ll");
   udm->execute();
   return 0;
}