#include "lifter/x86_64/X86_64ELFStrategy.h"

#include <memory>
#include <iostream>

#include "logger/LoggerManager.h"

#include "lifter/server/RetdecClient.h"
#include "settings/LifterSettings.h"


lifter::X86_64ELFStrategy::X86_64ELFStrategy() {
    logger = logger::LoggerManager::getInstance()->getLogger("lifter");
}

void lifter::X86_64ELFStrategy::lift(const std::string& file) {
    const std::string serverUrl = settings::LifterSettings::getInstance()->getServerUrl();
    if(serverUrl.empty()) {
        logger->error("[X86_64ELFStrategy::lift]Server URL is not set. Please set it in the settings.");
        return;
    }

    const std::string binaryPath = settings::LifterSettings::getInstance()->getBinaryPath();
    if(binaryPath.empty()) {
        logger->error("[X86_64ELFStrategy::lift]Binary path is not set. Please set it in the settings.");
        return;
    }

    server::RetdecClient client(serverUrl);
    CURLcode statusCode = client.uploadBinary(binaryPath);
    if(statusCode != CURLE_OK) {
        logger->error("[X86_64ELFStrategy::lift]Failed to upload binary: {}", binaryPath);
        return;
    }
    logger->info("[X86_64ELFStrategy::lift]Uploaded was uploaded succesfully: {}", binaryPath);

    statusCode = client.decompileBinary(binaryPath);
    if(statusCode != CURLE_OK) {
        logger->error("[X86_64ELFStrategy::lift]Failed to decompile binary: {}", binaryPath);
        return;
    }
    logger->info("[X86_64ELFStrategy::lift]Binary was decompiled succesfully: {}", binaryPath);

    statusCode = client.downloadIR(binaryPath);
    if(statusCode != CURLE_OK) {
        logger->error("Failed to download IR: {}", binaryPath);
        return;
    }
    logger->info("[X86_64ELFStrategy::lift]IR was downloaded succesfully: {}", binaryPath);
}
