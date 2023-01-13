#ifndef __FUNCTIONS_ANALYSIS_H__
#define __FUNCTIONS_ANALYSIS_H__

#include <iostream>
#include <vector>
#include <set>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>

namespace udm
{

class FunctionsAnalysis {
public:
    std::vector<std::set<llvm::BasicBlock *>> intervals(llvm::Function& f);     
private:
    std::string instructionToString(llvm::Instruction &I);
    bool allPredecessorsInInterval(std::vector<std::string> pred, std::set<llvm::BasicBlock*> interval);
    std::vector<std::string> getPredecessors(llvm::BasicBlock* bb);
};

} // namespace udm

#endif