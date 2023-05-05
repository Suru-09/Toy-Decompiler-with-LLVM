#include "lifter/server/RetdecClient.h"
#include "logger/LoggerManager.h"

#include <iostream>
#include <curl/curl.h>
#include <boost/property_tree/json_parser.hpp>

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

CURLcode server::RetdecClient::uploadBinary(const std::string& binaryPath) {
    const std::string uploadUrl = m_serverUrl + "/api/upload";
    const std::string binaryName = getBinaryName(binaryPath);
    logger->info("uploading binary to {}", uploadUrl);
    CURL *curl = curl_easy_init();
    if(!curl) {
        logger->error("[RetdecClient::uploadBinary] Failed to initialize curl");
        return CURLE_FAILED_INIT;
    }

    std::ifstream binaryFile(binaryPath, std::ios::binary);
    if(!binaryFile.is_open()) {
        logger->error("[RetdecClient::uploadBinary] Failed to open binary file: {}", binaryPath);
        return CURLE_FILE_COULDNT_READ_FILE;
    }

    std::stringstream binaryStream;
    binaryStream << binaryFile.rdbuf();
    std::string binaryContent = binaryStream.str();

    curl_easy_setopt(curl, CURLOPT_URL, uploadUrl.c_str());
    
    // Create the form data structure
    struct curl_httppost* formpost = NULL;
    struct curl_httppost* lastptr = NULL;

    // Add the binary file as a form field
    curl_formadd(&formpost, &lastptr,
                    CURLFORM_COPYNAME, "file",
                    CURLFORM_BUFFER, binaryName.c_str(),
                    CURLFORM_BUFFERPTR, binaryContent.data(),
                    CURLFORM_BUFFERLENGTH, binaryContent.size(),
                    CURLFORM_END);
    curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

    CURLcode res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
        logger->error("[RetdecClient::uploadBinary] Failed to upload binary: {}", curl_easy_strerror(res));
        return CURLE_UPLOAD_FAILED;
    }

    curl_easy_cleanup(curl);
    curl_formfree(formpost);
    
    return CURLE_OK;
}

CURLcode server::RetdecClient::decompileBinary(const std::string& binaryPath) {
    std::string binaryName = getBinaryName(binaryPath);
    std::string decompileUrl = m_serverUrl + "/api/decompile";
    logger->info("[RetdecClient::decompileBinary] decompiling binary at {}", decompileUrl);

    CURL *curl = curl_easy_init();
    if(!curl) {
        logger->error("[RetdecClient::decompileBinary] Failed to initialize curl");
        return CURLE_FAILED_INIT;
    }

    curl_easy_setopt(curl, CURLOPT_URL, decompileUrl.c_str());
    // if we don't set this option and try to set it directly curl will crash
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    // send binary file string in json format in post request with form { "file": binaryName }
    std::string json = "{\"file\": \"" + binaryName + "\"}";
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, json.size());

    CURLcode res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
        logger->error("[RetdecClient::decompileBinary] Failed to decompile binary: {}", curl_easy_strerror(res));
        return CURLE_UPLOAD_FAILED;
    }

    curl_easy_cleanup(curl);
    return CURLE_OK;
}

size_t write_data(void* ptr, size_t size, size_t nmemb, void* userdata) {
    FILE* file = (FILE*)userdata;
    return fwrite(ptr, size, nmemb, file);
}

void server::RetdecClient::convertJsonIRToPlainText(const std::string& llvmIRPath)
{
    std::ifstream jsonFile(llvmIRPath);
    if(!jsonFile.is_open()) {
        logger->error("[RetdecClient::convertJsonIRToPlainText] Failed to open json file: {}", llvmIRPath);
        return;
    }

    boost::property_tree::ptree pt;
    boost::property_tree::read_json(jsonFile, pt);
    const auto llvmIR = pt.get<std::string>("message");
    std::ofstream llvmIRFile(llvmIRPath );
    llvmIRFile << llvmIR;
    llvmIRFile.close();
}

CURLcode server::RetdecClient::downloadIR(const std::string& binaryPath) {
    const std::string binaryName = getBinaryName(binaryPath);
    const std::string downloadIRUri = m_serverUrl + "/api/ir?file=" + binaryName;
    logger->info("[RetdecClient::downloadIR] downloading IR at {}", downloadIRUri);

    CURL *curl = curl_easy_init();
    if(!curl) {
        logger->error("[downloadIR] Failed to initialize curl");
        return CURLE_FAILED_INIT;
    }

    const std::string downloadPath = binaryName + ".ll";
    FILE* irFile = fopen(downloadPath.c_str(), "wb");
    if(!irFile) {
        logger->error("[RetdecClient::downloadIR] Failed to open IR file: {}", downloadPath);
        return CURLE_FILE_COULDNT_READ_FILE;
    }

    // donwload the IR file
    curl_easy_setopt(curl, CURLOPT_URL, downloadIRUri.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, irFile);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

     CURLcode res = curl_easy_perform(curl);
     if(res != CURLE_OK) {
         logger->error("[RetdecClient::downloadIR] Failed to download IR from server {}", curl_easy_strerror(res));
         return CURLE_UPLOAD_FAILED;
     }

    fclose(irFile);
    // convert the json IR to plain text
    convertJsonIRToPlainText(downloadPath);

    curl_easy_cleanup(curl);
    return CURLE_OK;
}