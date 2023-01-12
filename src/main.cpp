#include <iostream>
#include <memory>

#include "utils/LifterUtils.h"
#include "udm/cfa/CFG.h"
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
   std::unique_ptr<udm::CFG> cfg = std::make_unique<udm::CFG>(testing_file + ".ll");
   cfg->execute();
   return 0;
}