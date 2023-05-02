#ifndef _RETDEC_CLIENT_H
#define _RETDEC_CLIENT_H

#include <memory>

#include "spdlog/spdlog.h"
#include <curl/curl.h>

namespace server {

class RetdecClient {

public:
RetdecClient(const std::string& serverUrl);
~RetdecClient() = default;

CURLcode uploadBinary(const std::string& binaryPath);
CURLcode decompileBinary(const std::string& binaryPath);
CURLcode downloadIR(const std::string& binaryPath);

private:
std::string m_serverUrl;
std::shared_ptr<spdlog::logger> logger;

private:
std::string getBinaryName(const std::string& binaryPath);

};

}   // namespace server

#endif