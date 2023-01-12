#ifndef _CFG__H
#define _CFG__H

#include <iostream>
#include <vector>

#include <llvm/IR/Instruction.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

namespace udm
{

class CFG {
public:
    CFG(const std::string& IRFile);
    void execute();
private:
    std::string irFile;

    std::string instructionToString(llvm::Instruction &I);
    std::vector<std::vector<llvm::BasicBlock *>> intervals(llvm::Function& f);
    bool allPredecessorsInInterval(std::vector<llvm::BasicBlock*> pred, std::vector<llvm::BasicBlock*> interval);
    std::vector<llvm::BasicBlock*> getPredecessors(llvm::BasicBlock* bb);
};
    
} // namespace udm



#endif