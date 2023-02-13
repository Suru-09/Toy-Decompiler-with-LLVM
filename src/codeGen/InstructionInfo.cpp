#include "codeGen/InstructionInfo.h"

#include "logger/LoggerManager.h"


codeGen::InstructionInfo::InstructionInfo(const std::string& instrName) 
: name(instrName),
loopType(udm::BBInfo::LoopType::NONE),
indentLevel(0),
loopIfCondition(""),
value("")
{
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}

codeGen::InstructionInfo::InstructionInfo()
: name(""),
loopType(udm::BBInfo::LoopType::NONE),
indentLevel(0),
loopIfCondition(""),
value("")
{
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}

bool codeGen::InstructionInfo::isEmpty() const {
    return name.empty();
}

bool codeGen::InstructionInfo::isLoop() const {
    return loopType != udm::BBInfo::LoopType::NONE;
}

bool codeGen::InstructionInfo::getShouldWriteElse() const {
    return shouldWriteElse;
}

bool codeGen::InstructionInfo::isIf() const {
    return !loopIfCondition.empty() && loopType == udm::BBInfo::LoopType::NONE;
}

void codeGen::InstructionInfo::setLoopIfCondition(const std::string& condition) {
    loopIfCondition = condition;
}

void codeGen::InstructionInfo::setSHouldWriteElse(bool shouldWriteElse) {
    this->shouldWriteElse = shouldWriteElse;
}

void codeGen::InstructionInfo::setLoopType(udm::BBInfo::LoopType type) {
    loopType = type;
}

void codeGen::InstructionInfo::setCloseBraces(bool closeBraces) {
    this->closeBraces = closeBraces;
}

bool codeGen::InstructionInfo::getCloseBraces() const {
    return closeBraces;
}

void codeGen::InstructionInfo::setIndentLevel(int64_t level) {
    indentLevel = level;
}

void codeGen::InstructionInfo::setName(const std::string& name) {
    this->name = name;
}

void codeGen::InstructionInfo::setValue(const std::string& value) {
    this->value = value;
}

const std::string& codeGen::InstructionInfo::getName() const {
    return name;
}

const std::string& codeGen::InstructionInfo::getValue() const {
    return value;
}

const std::string& codeGen::InstructionInfo::getLoopIfCondition() const {
    return loopIfCondition;
}

udm::BBInfo::LoopType codeGen::InstructionInfo::getLoopType() const {
    return loopType;
}

int64_t codeGen::InstructionInfo::getIndentLevel() const {
    return indentLevel;
}

std::string codeGen::InstructionInfo::toString() const
{
    std::string str = "";
    str += "name: " + name;
    str += ", value: " + value;
    str += ", loopIfCondition: " + loopIfCondition;
    str += ", loopType: " + std::to_string(static_cast<int>(loopType));
    str += ", indentLevel: " + std::to_string(indentLevel);
    str += ", shouldWriteElse: " + std::to_string(shouldWriteElse);
    str += ", closeBraces: " + std::to_string(closeBraces);
    return str;
}

void codeGen::InstructionInfo::clear() {
    name = "";
    value = "";
    loopIfCondition = "";
    loopType = udm::BBInfo::LoopType::NONE;
    indentLevel = 0;
}
