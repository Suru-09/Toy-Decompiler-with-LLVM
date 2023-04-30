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
        logger->error("Server URL is not set. Please set it in the settings.");
        return;
    }

    const std::string binaryPath = settings::LifterSettings::getInstance()->getBinaryPath();
    if(binaryPath.empty()) {
        logger->error("Binary path is not set. Please set it in the settings.");
        return;
    }

    server::RetdecClient client(serverUrl);
    web::http::status_code statusCode = client.uploadBinary(binaryPath);
    if(statusCode != web::http::status_codes::OK) {
        logger->error("Failed to upload binary: {}", binaryPath);
        return;
    }

    statusCode = client.decompileBinary(binaryPath);
    if(statusCode != web::http::status_codes::OK) {
        logger->error("Failed to decompile binary: {}", binaryPath);
        return;
    }

    statusCode = client.downloadIR(binaryPath);
    if(statusCode != web::http::status_codes::OK) {
        logger->error("Failed to download IR: {}", binaryPath);
        return;
    }
}
