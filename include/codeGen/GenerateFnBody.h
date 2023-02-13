#ifndef _GENERATE_FN_BODY_H_
#define _GENERATE_FN_BODY_H_

#include <iostream>
#include <map>
#include <set>

#include <llvm/IR/Function.h>

#include <spdlog/spdlog.h>

#include "udm/FuncInfo.h"
#include "udm/BBInfo.h"
#include "codeGen/InstructionInfoRepo.h"

namespace codeGen {

class GenerateFnBody {
public:
    GenerateFnBody(llvm::Function& function, const udm::FuncInfo funcInfo);
    ~GenerateFnBody() = default;

    std::string generate();
private:
    void populateInstructionInfoRepo(codeGen::InstructionInfoRepo& repo);
    void populateInstructionInfoRepoForBasicBlock(
        codeGen::InstructionInfoRepo& repo, llvm::BasicBlock* bb,
        int64_t numSpaces, codeGen::InstructionInfo& instrInfo
    );
    bool isBBSuccesorOf(llvm::BasicBlock* bb, llvm::BasicBlock* succBB);
    bool isBBPredecessorOf(llvm::BasicBlock* bb, llvm::BasicBlock* predBB);

    std::string getLastBlock();
    std::string getLoopCondition(llvm::Instruction& inst, int64_t numSpaces);

    bool isLoop(const udm::BBInfo& bbInfo);
    bool isLoopSelfContained(const udm::BBInfo& bbInfo, llvm::BasicBlock* bb);
    bool isConditionalBranch(const udm::BBInfo& bbInfo);

    llvm::Function& fn;
    udm::FuncInfo funcInfo;
    std::map<std::pair<std::string, std::string>, std::string> expandedInstructions;
    std::shared_ptr<spdlog::logger> logger;
};

}   // namespace codeGen

#endif // _GENERATE_FN_BODY_H_