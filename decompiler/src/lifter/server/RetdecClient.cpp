#include "lifter/server/RetdecClient.h"

#include <iostream>
#include <filesystem>

#include "logger/LoggerManager.h"
#include <spdlog/spdlog.h>


server::RetdecClient::RetdecClient(const std::string& serverUrl) 
: m_serverUrl(serverUrl) 
{
    logger = logger::LoggerManager::getInstance()->getLogger("lifter");
}

std::string server::RetdecClient::getBinaryName(const std::string& binaryPath) {
    size_t lastSlash = binaryPath.find_last_of('/');
    if(lastSlash == std::string::npos) {
        return binaryPath;
    }
    return binaryPath.substr(lastSlash + 1);
}

web::http::status_code server::RetdecClient::uploadBinary(const std::string& binaryPath) {
    std::string binaryName = getBinaryName(binaryPath);
    std::string uploadUrl = m_serverUrl + "/upload/" + binaryName;
    logger->info("uploading binary to {}", uploadUrl);
    web::http::client::http_client client(uploadUrl);
    web::http::status_code statusCode = web::http::status_codes::OK;
    try {
        pplx::task<web::http::http_response> response = client.request(web::http::methods::PUT, binaryPath);
        response.wait();
        statusCode = response.get().status_code();
        statusCode == web::http::status_codes::OK ? logger->info("Binary uploaded successfully") : logger->error("Binary upload failed");
    } catch(const std::exception& e) {
        logger->error("Exception while uploading binary");
    }
    return statusCode;
}

web::http::status_code server::RetdecClient::decompileBinary(const std::string& binaryPath) {
    std::string binaryName = getBinaryName(binaryPath);
    std::string decompileUrl = m_serverUrl + "/decompile/" + binaryName;
    //logger->info("decompiling binary at {}", decompileUrl);
    web::http::client::http_client client(decompileUrl);
    web::http::status_code statusCode = web::http::status_codes::OK;
    try {
        pplx::task<web::http::http_response> response = client.request(web::http::methods::POST);
        response.wait();
        statusCode = response.get().status_code();
       statusCode == web::http::status_codes::OK ? logger->info("Binary decompiled successfully") : logger->error("Binary decompilation failed");
    } catch(const std::exception& e) {
        logger->error("Exception while decompiling binary");
    }
    return statusCode;
}

web::http::status_code server::RetdecClient::downloadIR(const std::string& binaryPath) {
    std::string binaryName = getBinaryName(binaryPath);
    std::string downloadUrl = m_serverUrl + "/download/" + binaryName;
    logger->info("downloading IR from {}", downloadUrl);
    web::http::client::http_client client(downloadUrl);
    web::http::status_code statusCode = web::http::status_codes::OK;
    try {
        pplx::task<web::http::http_response> response = client.request(web::http::methods::GET);
        response.wait();
        statusCode = response.get().status_code();
        if(statusCode == web::http::status_codes::OK) {
            std::string irFileName = binaryName + ".ll";
            std::string downloadsDir = std::filesystem::current_path().parent_path().parent_path().string() + "/downloads";
            if (!std::filesystem::exists(downloadsDir)) {
                std::filesystem::create_directory(downloadsDir);
            }
            std::string irFilePath = downloadsDir + "/ir/" + irFileName; 
            std::ofstream irFile(irFilePath);
            irFile << response.get().extract_string().get();
            irFile.close();
            logger->info("IR downloaded to {}", irFilePath);
        }
    } catch(const std::exception& e) {
        logger->error("Exception while downloading IR");
    }
    return statusCode;
}