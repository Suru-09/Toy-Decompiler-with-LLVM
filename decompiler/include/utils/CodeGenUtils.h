#ifndef _CODE_GEN_UTILS_H_
#define _CODE_GEN_UTILS_H_

#include <iostream>

#include <llvm/IR/Value.h>
#include "llvm/IR/Type.h"
#include "llvm/IR/User.h"
#include "llvm/IR/Instruction.h"

#include "udm/FuncInfo.h"

namespace utils
{

class CodeGenUtils
{
public:
    static std::string getSpaces(int numSpaces);
    static std::string typeToString(llvm::Type* type);
    static bool canAssignTo(llvm::Instruction* instr);
    static std::vector<std::string> extractLabelsFromPhiString(const std::string& phiString);
    static std::vector<std::string> extractValuesFromPhiString(const std::string& phiString);
    static std::string extractPhiNodeLeftValue(const std::string& phiString);
    static bool isLoop(const udm::FuncInfo& funcInfo, const std::string& bbLabel);
    static std::string getLoopCondition(llvm::Function& func, const std::string& bbLabel);
    static std::vector<std::string> extractSubstrings(const std::string& input, const std::string& substr);
};

}   // namespace utils

#endif