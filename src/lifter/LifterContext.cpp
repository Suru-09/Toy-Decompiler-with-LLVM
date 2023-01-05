#include "lifter/LifterContext.h"

#include <iostream>

#include "lifter/ELFVisitor.h"
#include "lifter/ExecutableType.h"

void lifter::LifterContext::setStrategy(std::shared_ptr<IArchitectureStrategy> strategy) {
    this->strategy = std::move(strategy);
}

lifter::LifterContext::LifterContext(const std::string& file)
: file(file), strategy(nullptr)
{}


void lifter::LifterContext::executeStrategy() {
    if(strategy != nullptr) {
        ExecutableType::getBinaryType(file);
        std::shared_ptr<lifter::ELFVisitor> elfVisitor = std::make_shared<lifter::ELFVisitor>(shared_from_this());
        strategy->visit(elfVisitor);
    }
}