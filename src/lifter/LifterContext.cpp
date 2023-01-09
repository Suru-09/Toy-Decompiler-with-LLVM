#include "lifter/LifterContext.h"

#include <iostream>

#include "lifter/ExecutableType.h"

void lifter::LifterContext::setStrategy(std::shared_ptr<IArchitectureStrategy> strategy) {
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

std::string& lifter::LifterContext::getFile() {
    return file;
}