#include "lifter/x86_64/X86_64StrategyFactory.h"

#include "lifter/x86_64/X86_64ELFStrategy.h"
#include "spdlog/spdlog.h"

std::unique_ptr<lifter::IArchitectureStrategy> 
    lifter::X86_64StrategyFactory::createStrategy(ExecutableType::BinaryType binType) 
{
    switch (binType)
    {
    case ExecutableType::BinaryType::ELF:
        return std::make_unique<lifter::X86_64ELFStrategy>();
    default:
        spdlog::critical("Given binary type: <{}> is not yet supported!", (int)binType);
        return nullptr;
    }
}