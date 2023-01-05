#ifndef __STRATEGY_FACTORY__H
#define __STRATEGY_FACTORY__H

#include "IArchitectureStrategy.h"
#include <llvm/Object/Binary.h>

#include <memory>

namespace lifter
{

class StrategyFactory {
public:
    static std::shared_ptr<IArchitectureStrategy> createStrategy(llvm::Triple::ArchType arch);
};

} // namespace lifter


#endif