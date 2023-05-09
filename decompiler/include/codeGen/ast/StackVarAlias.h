#ifndef REVERSE_ENGINEERING_TOOL_STACKVARALIAS_H
#define REVERSE_ENGINEERING_TOOL_STACKVARALIAS_H

#include <string>
#include <memory>
#include <spdlog/spdlog.h>

namespace codeGen::ast
{

class StackVarAlias {
public:
    StackVarAlias() = default;
    StackVarAlias(const StackVarAlias&) = default;
    StackVarAlias(StackVarAlias&&) = default;
    StackVarAlias& operator=(const StackVarAlias&) = default;
    StackVarAlias& operator=(StackVarAlias&&) = default;
    ~StackVarAlias() = default;

    StackVarAlias(const std::string& basicBlockName, const std::string& localVar, const std::string& stackVarName);

    const std::string& getBasicBlockName() const;
    const std::string& getLocalVar() const;
    const std::string& getStackVarName() const;

    void setBasicBlockName(const std::string& basicBlockName);
    void setLocalVar(const std::string& localVar);
    void setStackVarName(const std::string& stackVarName);
private:
    std::string m_basicBlockName;
    std::string m_localVar;
    std::string m_stackVarName;
    std::shared_ptr<spdlog::logger> logger;
};

}   // namespace codeGen


#endif //REVERSE_ENGINEERING_TOOL_STACKVARALIAS_H
