#ifndef __ARMSTRATEGY_FACTORY__H
#define __ARMSTRATEGY_FACTORY__H


#include "StrategyFactory.h"
#include <llvm/Object/Binary.h>


#include <memory>

namespace lifter
{

class ARM64StrategyFactory : public StrategyFactory {
public:
    std::shared_ptr<IArchitectureStrategy> createStrategy(ExecutableType::BinaryType binType);
};

} // namespace lifter


#endif