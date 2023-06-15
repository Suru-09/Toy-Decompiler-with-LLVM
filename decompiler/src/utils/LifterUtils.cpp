#include "utils/LifterUtils.h"

#include <spdlog/spdlog.h>

#include "lifter/ExecutableType.h"
#include "lifter/StrategyFactory.h"
#include "settings/LifterSettings.h"

#include <filesystem>
#include <fstream>

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

void utils::cleanDownloadedFiles(std::size_t threshold)
{
    // count the number of files in the downloads folder
    std::size_t count = 0;
    for (const auto& entry : std::filesystem::directory_iterator("../downloads"))
        count++;

    // if the number of files is greater than the threshold, delete all files
    if(count <= threshold)
        return;

    try
    {
        for (const auto& entry : std::filesystem::directory_iterator("../downloads"))
        {
            std::filesystem::remove(entry.path());
        }
    }
    catch(const std::exception& e)
    {
        spdlog::error("Error while deleting files from downloads folder: {}", e.what());
    }
}