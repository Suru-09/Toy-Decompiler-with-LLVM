#include "lifter/StrategyFactory.h"

#include "lifter/X86Strategy.h"
#include "lifter/ARM64Strategy.h"

#include <iostream>

std::shared_ptr<lifter::IArchitectureStrategy> lifter::StrategyFactory::createStrategy(llvm::Triple::ArchType arch)
{
    const char* archStr = llvm::Triple::getArchTypeName(arch).data();
    switch(arch) {
        case llvm::Triple::x86_64:
            return std::make_shared<lifter::X86Strategy>();
        case llvm::Triple::arm:
            return std::make_shared<lifter::ARM64Strategy>();
        default:
            std::cout << "Architecture: [" << archStr << "] is not supported yet!";
            exit(1);
    }   
}

