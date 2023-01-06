#include "lifter/VisitorFactory.h"

#include "lifter/ELFVisitor.h"

#include <iostream>
#include <memory>


lifter::VisitorFactory::VisitorFactory(std::shared_ptr<lifter::LifterContext> lifter) 
: lifterContext(lifter) {}

std::shared_ptr<lifter::IVisitor> lifter::VisitorFactory::createVisitor(lifter::ExecutableType::BinaryType binType)
{
    switch(binType) {
        case lifter::ExecutableType::BinaryType::ELF:
            return std::make_shared<lifter::ELFVisitor>(lifterContext->getFile());
        case lifter::ExecutableType::BinaryType::PE:
        case lifter::ExecutableType::BinaryType::MACH_O:
        case lifter::ExecutableType::BinaryType::OTHER:
        case lifter::ExecutableType::BinaryType::ERROR:
        default:
            std::cout << "Given executable format is not supported yet!";
            exit(1);
    }   
}

