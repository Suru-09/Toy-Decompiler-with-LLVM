#include <iostream>
#include <memory>

#include "lifter/IArchitectureStrategy.h"
#include "lifter/LifterContext.h"
#include "lifter/StrategyFactory.h"
#include "lifter/ExecutableType.h"

#include "spdlog/spdlog.h"


int main(int argc, char** argv) {
    std::string testing_file = "../test/plm.exe";

    std::shared_ptr<lifter::LifterContext> lifterCtx =  
      std::make_shared<lifter::LifterContext>(lifter::LifterContext{testing_file});
    std::shared_ptr<lifter::IArchitectureStrategy> strategy = 
        lifter::StrategyFactory::createStrategy(lifter::ExecutableType::getArchType(testing_file));

    lifterCtx->setStrategy(std::move(strategy));
    lifterCtx->executeStrategy();

    if(!strategy) {
        std::cout << "Strategy is null after beeing moved\n";
    }
    else {
        std::cout << "Strategy is NOT null after beeing moved\n";
    }

    return 0;
}