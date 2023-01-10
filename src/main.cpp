#include <iostream>
#include <memory>

#include "utils/LifterUtils.h"

#include "spdlog/spdlog.h"


int main(int argc, char** argv) {
     std::string testing_file = "../testing_files/elfC/fibbo_c";

     std::shared_ptr<lifter::LifterContext> lifterCtx = utils::getLifterCtx(testing_file);

     if(!lifterCtx)
     {
        spdlog::critical("Invalid lifterContext created(nullptr)!");
        exit(1);
     }
     
     lifterCtx->executeStrategy();

    return 0;
}