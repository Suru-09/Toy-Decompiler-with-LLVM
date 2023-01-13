#ifndef __FUNCTIONS_ANALYSIS_H__
#define __FUNCTIONS_ANALYSIS_H__

#include <iostream>
#include <vector>
#include <set>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>

#include "udm/Interval.h"

namespace udm
{

class FunctionsAnalysis {
public:
    std::vector<udm::Interval> intervals(llvm::Function& f);     
private:
    std::string instructionToString(llvm::Instruction &I);
    bool allPredecessorsInInterval(const std::vector<std::string>& pred, const udm::Interval& interval) const;
    std::vector<std::string> getPredecessors(llvm::BasicBlock* bb);
};

} // namespace udm

#endif