#include "codeGen/Variable.h"
#include "logger/LoggerManager.h"


codeGen::Variable::Variable(const std::string& name, const std::string& type, const std::string& initialValue)
: name(name),
type(type),
initialValue(initialValue)
{
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}


std::string codeGen::Variable::getName() const {
    return name;
}

std::string codeGen::Variable::getType() const {
    return type;
}

std::string codeGen::Variable::getInitialValue() const {
    return initialValue;
}

void codeGen::Variable::setName(const std::string& name) {
    this->name = name;
}

void codeGen::Variable::setType(const std::string& type) {
    this->type = type;
}

void codeGen::Variable::setInitialValue(const std::string& initialValue) {
    this->initialValue = initialValue;
}