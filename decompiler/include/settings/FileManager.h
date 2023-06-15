#ifndef REVERSE_ENGINEERING_TOOL_FILEMANAGER_H
#define REVERSE_ENGINEERING_TOOL_FILEMANAGER_H

#include <unordered_map>
#include <string>

namespace settings {

class FileManager {
public:
    ~FileManager() = default;

    virtual void writeToFile(const std::string& filename, const std::unordered_map<std::string, std::string>& settings) = 0;
    virtual std::unordered_map<std::string, std::string> readFromFile(const std::string& filename) = 0;
};

}

#endif //REVERSE_ENGINEERING_TOOL_FILEMANAGER_H
