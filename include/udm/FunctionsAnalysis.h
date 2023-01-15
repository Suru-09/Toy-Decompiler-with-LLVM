#ifndef __FUNCTIONS_ANALYSIS_H__
#define __FUNCTIONS_ANALYSIS_H__

#include <iostream>
#include <vector>
#include <unordered_map>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>

#include "udm/Interval.h"
#include "udm/FuncInfo.h"

namespace udm
{

class FunctionsAnalysis {
public:
    std::vector<udm::Interval> intervals(llvm::Function& f, udm::FuncInfo& funcInfo);
    std::unordered_map<std::string, udm::FuncInfo> getFunctionsInfo() const;
private:
    std::string instructionToString(llvm::Instruction &I);
    bool allPredecessorsInInterval(const std::vector<std::string>& pred, const udm::Interval& interval) const;

    std::unordered_map<std::string, udm::FuncInfo> functionsInfo;
};

} // namespace udm

#endif