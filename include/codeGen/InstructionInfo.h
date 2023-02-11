#ifndef _INSTRUCTION_INFO_H_
#define _INSTRUCTION_INFO_H_

#include <iostream>

#include <spdlog/spdlog.h>

#include "udm/BBInfo.h"


namespace codeGen {

class InstructionInfo {
public:
    InstructionInfo(const std::string& instrName);
    InstructionInfo();
    ~InstructionInfo() = default;

    bool isEmpty() const;
    bool isLoop() const;
    bool isIf() const;

    void setLoopIfCondition(const std::string& condition);
    void setLoopType(udm::BBInfo::LoopType type);
    void setIndentLevel(int64_t level);
    void setName(const std::string& name);
    void setValue(const std::string& value);

    const std::string& getName() const;
    const std::string& getValue() const;
    const std::string& getLoopIfCondition() const;
    udm::BBInfo::LoopType getLoopType() const;
    int64_t getIndentLevel() const;

    std::string toString() const;
    void clear();

private:
    std::string name;
    std::string value;
    std::string loopIfCondition;
    udm::BBInfo::LoopType loopType;
    int64_t indentLevel;
    std::shared_ptr<spdlog::logger> logger;
};

}   // namespace codeGen

#endif  // _INSTRUCTION_INFO_H_