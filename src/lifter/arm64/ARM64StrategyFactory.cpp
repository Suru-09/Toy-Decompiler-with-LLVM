#include "lifter/arm64/ARM64StrategyFactory.h"


#include "lifter/arm64/ARM64ELFStrategy.h"

std::shared_ptr<lifter::IArchitectureStrategy> 
    lifter::ARM64StrategyFactory::createStrategy(ExecutableType::BinaryType binType) 
{
    switch (binType)
    {
    case ExecutableType::BinaryType::ELF:
        return std::make_shared<lifter::ARM64ELFStrategy>();
    default:
        return nullptr;
    }
}