#ifndef REVERSE_ENGINEERING_TOOL_VARIABLE_H
#define REVERSE_ENGINEERING_TOOL_VARIABLE_H

#include <string>
#include <memory>
#include <spdlog/spdlog.h>


namespace codeGen {

class Variable {
public:
    explicit Variable(const std::string& name, const std::string& type, const std::string& initialValue);
    ~Variable() = default;

    std::string getName() const;
    std::string getType() const;
    std::string getInitialValue() const;

    void setName(const std::string& name);
    void setType(const std::string& type);
    void setInitialValue(const std::string& initialValue);
private:
    std::string name;
    std::string type;
    std::string initialValue;
    std::shared_ptr<spdlog::logger> logger;
};

}     // namespace codeGen

#endif //REVERSE_ENGINEERING_TOOL_VARIABLE_H
