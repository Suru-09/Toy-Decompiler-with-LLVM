#include "lifter/LifterContext.h"

#include <iostream>

#include "lifter/ExecutableType.h"
#include "settings/LifterSettings.h"

void lifter::LifterContext::setStrategy(std::shared_ptr<IArchitectureStrategy> strategy) {
    this->strategy = std::move(strategy);
}

lifter::LifterContext::LifterContext()
: strategy(nullptr)
{
    file = settings::LifterSettings::getInstance()->getBinaryPath();
}


void lifter::LifterContext::executeStrategy() {
    if(strategy != nullptr) {
        strategy->lift(file);
    }
}
