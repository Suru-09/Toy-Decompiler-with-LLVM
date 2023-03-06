#include "lifter/arm64/ARM64StrategyFactory.h"

#include "lifter/arm64/ARM64ELFStrategy.h"

#include "spdlog/spdlog.h"

std::unique_ptr<lifter::IArchitectureStrategy> 
    lifter::ARM64StrategyFactory::createStrategy(ExecutableType::BinaryType binType) 
{
    switch (binType)
    {
    case ExecutableType::BinaryType::ELF:
        return std::make_unique<lifter::ARM64ELFStrategy>();
    default:
        spdlog::critical("Given binary type: <{}> is not yet supported!", (int)binType);
        return nullptr;
    }
}