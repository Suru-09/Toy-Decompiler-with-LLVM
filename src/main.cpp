#include <iostream>
#include <memory>

#include "lifter/IArchitectureStrategy.h"
#include "lifter/LifterContext.h"
#include "lifter/ARM64Strategy.h"

int main(int argc, char** argv) {
    
    lifter::LifterContext lifterCtx = lifter::LifterContext{"test.o"};
    std::unique_ptr<lifter::IArchitectureStrategy> strategy = std::make_unique<lifter::ARM64Strategy>();
    lifterCtx.setStrategy(std::move(strategy));

    if(!strategy) {
        std::cout << "Strategy is null after beeing moved\n";
    }
    else {
       std::cout << "Strategy is NOT null after beeing moved\n";
    }
    return 0;
}
