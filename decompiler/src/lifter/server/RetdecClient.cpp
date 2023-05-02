#include "lifter/server/RetdecClient.h"

#include <iostream>
#include <filesystem>

#include "logger/LoggerManager.h"
#include <spdlog/spdlog.h>

#include "pplx/pplxtasks.h"
#include "cpprest/http_client.h"
#include "cpprest/filestream.h"


server::RetdecClient::RetdecClient(const std::string& serverUrl) 
: m_serverUrl(serverUrl) 
{
    logger = logger::LoggerManager::getInstance()->getLogger("lifter");
}

std::pair<std::string, std::string> generate_form_data(std::ifstream &strm, const std::string& file) {
    std::stringstream data;

    std::string boundary{};
    for (int i = 0; i < 50; i++) {
        boundary += (rand() % 26) + 'A';
    }

    std::cout << file << std::endl;
    data << "--" << boundary << "\n";
    data << "Content-Disposition: form-data; name=\"file\"; filename=\""
            << file << "\"\nContent-Type: application/octet-stream\n\n"
            << std::string((std::istreambuf_iterator<char>(strm)),
                           (std::istreambuf_iterator<char>())) << "\n\n";
    data << "--" << boundary << "--";

    return { boundary, data.str() };
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
    std::string uploadUrl = m_serverUrl + "/api/upload";
    
    web::http::client::http_client client(uploadUrl);

    auto postJson = pplx::create_task([&]() {
        // Create an http_request object with PUT method and set the binary file as the request body
        web::http::http_request request(web::http::methods::POST);
        request.set_request_uri(uploadUrl);
        std::ifstream binaryStream(binaryPath);
        auto p = generate_form_data(binaryStream, binaryName);
        std::cout << p.second << std::endl;
        request.set_body(p.second, "multipart/form-data; boundary=" + p.first);
        request.headers().add("Accept", "*/*");
        // Set the content type header to "application/octet-stream"
        // Send the http request to the server
        logger->info("Request to string: {}, {}", request.to_string(), request.body());
        return client.request(request);
    }).then([&](web::http::http_response response) {
        // Print the status code and response body to the console
        logger->info("Binary uploaded with status code {}", response.status_code());
        return response.extract_string();
    }).then([&](std::string responseString) {
        logger->info("Response string: {}", responseString);
    }).wait();
    return web::http::status_codes::NotImplemented;
}

web::http::status_code server::RetdecClient::decompileBinary(const std::string& binaryPath) {
    std::string binaryName = getBinaryName(binaryPath);
    std::string decompileUrl = m_serverUrl + "/api/decompile/" + binaryName;
    //logger->info("decompiling binary at {}", decompileUrl);
    web::json::value postData;
    postData["file"] = web::json::value::string(U(binaryName));
    web::http::client::http_client client(decompileUrl);
    web::http::status_code statusCode = web::http::status_codes::OK;
    try {
        pplx::task<web::http::http_response> response = client.request(web::http::methods::POST, binaryPath, postData);
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
    std::string downloadUrl = m_serverUrl + "/api/ir/" + binaryName;
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