#ifndef _INSTRUCTION_INFO_REPO_H_
#define _INSTRUCTION_INFO_REPO_H_

#include <iostream>
#include <vector>

#include <spdlog/spdlog.h>

#include "InstructionInfo.h"

namespace codeGen {

class InstructionInfoRepo {
public:
    InstructionInfoRepo();
    ~InstructionInfoRepo() = default;

    void insert(InstructionInfo& info);
    void remove(InstructionInfo& info);
    void update(InstructionInfo& info);
    InstructionInfo getInstructionInfo(const std::string& instrInfoName);

    // iterators
    std::vector<InstructionInfo>::iterator begin() { return repo.begin(); }
    std::vector<InstructionInfo>::iterator end() { return repo.end(); }
    std::vector<InstructionInfo>::const_iterator begin() const { return repo.begin(); }
    std::vector<InstructionInfo>::const_iterator end() const { return repo.end(); }

    std::string toString() const;

private:
    std::vector<InstructionInfo> repo;
    std::shared_ptr<spdlog::logger> logger;
};

}   // namespace codeGen

#endif  // _INSTRUCTION_INFO_REPO_H_