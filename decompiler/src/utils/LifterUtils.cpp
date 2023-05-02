#include "utils/LifterUtils.h"

#include <spdlog/spdlog.h>

#include "lifter/ExecutableType.h"
#include "lifter/StrategyFactory.h"

#include "settings/LifterSettings.h"

std::unique_ptr<lifter::IArchitectureStrategy> utils::getStrategy() 
{
    const std::string& testingFile = settings::LifterSettings::getInstance()->getBinaryPath();
    llvm::Triple::ArchType arch = lifter::ExecutableType::getArchType(testingFile);
    lifter::ExecutableType::BinaryType binType = lifter::ExecutableType::getBinaryType(testingFile);
    std::shared_ptr<lifter::StrategyFactory> factory = lifter::StrategyFactory::getArch(arch);
    return factory->createStrategy(binType);
}

std::shared_ptr<::lifter::LifterContext> utils::getLifterCtx()
{
    auto liftertCtx = std::make_shared<lifter::LifterContext>();
    auto strategy = utils::getStrategy();
    if(!strategy) {
        spdlog::critical("Invalid strategy created(nullptr)!");
        return nullptr;
    }
    liftertCtx->setStrategy(std::move(strategy));

    return liftertCtx;
}