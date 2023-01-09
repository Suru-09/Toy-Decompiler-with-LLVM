#include "lifter/x86_64/X86_64StrategyFactory.h"

#include "lifter/x86_64/X86_64ELFStrategy.h"

std::shared_ptr<lifter::IArchitectureStrategy> 
    lifter::X86_64StrategyFactory::createStrategy(ExecutableType::BinaryType binType) 
{
    switch (binType)
    {
    case ExecutableType::BinaryType::ELF:
        return std::make_shared<lifter::X86_64ELFStrategy>();
    default:
        return nullptr;
    }
}