#include "utils/LifterUtils.h"

#include "lifter/ExecutableType.h"
#include "lifter/StrategyFactory.h"


std::unique_ptr<lifter::IArchitectureStrategy> utils::getStrategy(const std::string& testingFile) 
{
    llvm::Triple::ArchType arch = lifter::ExecutableType::getArchType(testingFile);
    lifter::ExecutableType::BinaryType binType = lifter::ExecutableType::getBinaryType(testingFile);
    std::shared_ptr<lifter::StrategyFactory> factory = lifter::StrategyFactory::getArch(arch);
    return factory->createStrategy(binType);
}

std::shared_ptr<::lifter::LifterContext> utils::getLifterCtx(const std::string& testingFile)
{
    auto factory = getStrategy(testingFile);
    auto liftertCtx = std::make_shared<lifter::LifterContext>(lifter::LifterContext{testingFile});
    auto strategy = utils::getStrategy(testingFile);
    liftertCtx->setStrategy(std::move(strategy));

    return liftertCtx;
}