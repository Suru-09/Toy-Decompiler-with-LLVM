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
    struct BranchToTerminalBlockResult
    {
        bool isBranchingToTerminalBlock;
        bool isConditionReversed;
    };

public:
    static std::string getSpaces(std::size_t numSpaces);
    static std::string typeToString(llvm::Type* type);
    static bool canAssignTo(llvm::Instruction* instr);
    static std::vector<std::string> extractLabelsFromPhiString(const std::string& phiString);
    static std::vector<std::string> extractValuesFromPhiString(const std::string& phiString);
    static std::string extractPhiNodeLeftValue(const std::string& phiString);
    static bool isLoop(const udm::FuncInfo& funcInfo, const std::string& bbLabel);
    static std::pair<std::string, std::string> getTerminatorCondition(llvm::Function& func, const std::string& bbLabel);
    static std::vector<std::string> extractSubstrings(const std::string& input, const std::string& substr);
    static std::string getInstructionValue(const llvm::Instruction* instr);
    static std::string llvmValueToString(llvm::Value* value);
    static bool doesInstructionHaveSingleUse(const llvm::Instruction* instr);

    [[nodiscard("Possible nullptr returned!")]]
        static llvm::BasicBlock* getBBAfterLabel(llvm::Function& func, const std::string& bbLabel);

    [[nodiscard("Possible nullptr returned!")]]
    static llvm::Instruction *
    getInstructionAfterLabel(llvm::Function &func, const std::string &instrLabel, bool isReturn);

    static std::string getTerminatorAlias(llvm::Function& func, const llvm::Instruction* instr);

    static std::string getBranchInstrBodyGivenBlock(llvm::Function& func, const std::string& bbLabel);

    static std::string extractLHSFromInstructionBody(const std::string& instrBody);
    static std::string extractRHSFromInstructionBody(const std::string& instrBody);

    static BranchToTerminalBlockResult checkIfCurrentBlockBranchesToTerminalBlock(llvm::Function& func, const std::string& bbLabel);
    static std::string returnStringForBranchingToTerminalBlock(llvm::Function& func, const std::string& bbLabel);
    static bool isBasicBlockTerminal(llvm::Function& func, const std::string& bbLabel);
    static bool isInstructionUsedInTernaryOperatorAndHasSingleUse(const llvm::Instruction* instr);

    static bool doesFunctionCallReturn(const llvm::CallInst* callInst);
    static bool isInstructionAnArgumentToTheLLVMFunction(const llvm::Function& func, const std::string& instrLabel);
    static bool isLoopConditionReversed(const std::string& loopBasicBlockLabel, llvm::Function& func);
    static bool isFirstBlockBeforeSecondBlock(const std::string& firstBlockLabel, const std::string& secondBlockLabel, llvm::Function& func);
};

}   // namespace utils

#endif