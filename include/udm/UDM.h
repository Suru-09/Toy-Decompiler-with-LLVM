#ifndef _CFG__H
#define _CFG__H

#include <iostream>
#include <vector>
#include <set>

#include <llvm/IR/Instruction.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

namespace udm
{

class UDM {
public:
    UDM(const std::string& IRFile);
    void execute();
private:
    std::string irFile;

    std::string instructionToString(llvm::Instruction &I);
    std::vector<std::set<llvm::BasicBlock *>> intervals(llvm::Function& f);
    bool allPredecessorsInInterval(std::vector<std::string> pred, std::set<llvm::BasicBlock*> interval);
    std::vector<std::string> getPredecessors(llvm::BasicBlock* bb);
};
    
} // namespace udm



#endif