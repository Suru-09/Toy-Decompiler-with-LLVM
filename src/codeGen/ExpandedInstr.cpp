#include "codeGen/ExpandedInstr.h"

#include "logger/LoggerManager.h"

codeGen::ExpandedInstr::ExpandedInstr(std::string bbName, std::string instrName)
: bbName(bbName),
instrName(instrName)
{
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}

std::string codeGen::ExpandedInstr::getBBName() const {
    return bbName;
}

std::string codeGen::ExpandedInstr::getInstrName() const {
    return instrName;
}

std::string codeGen::ExpandedInstr::getExpandedInstr() const {
    return expandedInstr;
}

void codeGen::ExpandedInstr::setBBName(std::string bbName) {
    this->bbName = bbName;
}

void codeGen::ExpandedInstr::setInstrName(std::string instrName) {
    this->instrName = instrName;
}

void codeGen::ExpandedInstr::setExpandedInstr(std::string expandedInstr) {
    this->expandedInstr = expandedInstr;
}

bool codeGen::ExpandedInstr::operator==(const ExpandedInstr& other) const {
    return (instrName == other.instrName);
}