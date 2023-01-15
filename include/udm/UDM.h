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
    void printLoops(llvm::Function& f);
private:
    std::string irFile;
};
    
} // namespace udm



#endif