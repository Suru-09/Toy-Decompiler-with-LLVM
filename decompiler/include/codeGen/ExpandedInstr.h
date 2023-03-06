#ifndef _EXPANDED_INSTR_H_
#define _EXPANDED_INSTR_H_

#include <iostream>

#include <spdlog/spdlog.h>

namespace codeGen {

class ExpandedInstr {
public:
    ExpandedInstr(std::string bbName, std::string instrName);

    std::string getBBName() const ;
    std::string getInstrName() const;
    std::string getExpandedInstr() const;

    void setBBName(std::string bbName);
    void setInstrName(std::string instrName);
    void setExpandedInstr(std::string expandedInstr);

    bool operator==(const ExpandedInstr& other) const;

private:
    std::string bbName;
    std::string instrName;
    std::string expandedInstr;
    std::shared_ptr<spdlog::logger> logger;
};

}   // namespace codeGen


#endif // _EXPANDED_INSTR_H_