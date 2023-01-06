#include "lifter/LifterContext.h"

#include <iostream>

#include "lifter/ExecutableType.h"
#include "lifter/VisitorFactory.h"

void lifter::LifterContext::setStrategy(std::shared_ptr<IArchitectureStrategy> strategy) {
    this->strategy = std::move(strategy);
}

lifter::LifterContext::LifterContext(const std::string& file)
: file(file), strategy(nullptr)
{}


void lifter::LifterContext::executeStrategy() {
    if(strategy != nullptr) {
        auto binaryType = ExecutableType::getBinaryType(file);
        std::shared_ptr<lifter::VisitorFactory> visitorFactory = 
            std::make_shared<lifter::VisitorFactory>(shared_from_this());
        auto visitor = visitorFactory->createVisitor(binaryType);
        strategy->visit(visitor);
    }
}

std::string& lifter::LifterContext::getFile() {
    return file;
}