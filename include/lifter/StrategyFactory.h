#ifndef __STRATEGY_FACTORY__H
#define __STRATEGY_FACTORY__H


#include "lifter/ExecutableType.h"
#include "IArchitectureStrategy.h"
#include <llvm/Object/Binary.h>

#include <memory>

namespace lifter
{

class StrategyFactory {
public:
    virtual std::shared_ptr<IArchitectureStrategy> createStrategy(ExecutableType::BinaryType binType) = 0;
    static std::shared_ptr<StrategyFactory> getStrategy(llvm::Triple::ArchType arch);
};

} // namespace lifter


#endif