#include "lifter/LifterContext.h"

void lifter::LifterContext::setStrategy(std::unique_ptr<IArchitectureStrategy> strategy) {
    this->strategy = std::move(strategy);
}

lifter::LifterContext::LifterContext(const std::string& file)
: file(file), strategy(nullptr)
{}


void lifter::LifterContext::executeStrategy() {
    if(strategy != nullptr) {
        strategy->lift(file);
    }
}