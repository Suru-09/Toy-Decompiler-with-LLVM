#ifndef _GENERATE_FN_BODY_H_
#define _GENERATE_FN_BODY_H_

#include <iostream>
#include <map>
#include <set>

#include <llvm/IR/Function.h>

#include <spdlog/spdlog.h>

#include "udm/FuncInfo.h"
#include "codeGen/InstructionInfoRepo.h"

namespace codeGen {

class GenerateFnBody {
public:
    GenerateFnBody(llvm::Function& function, const udm::FuncInfo funcInfo);
    ~GenerateFnBody() = default;

    std::string generate();
private:
    void populateInstructionInfoRepo(codeGen::InstructionInfoRepo& repo);
    bool isBBSuccesorOf(llvm::BasicBlock* bb, llvm::BasicBlock* succBB);
    bool isBBPredecessorOf(llvm::BasicBlock* bb, llvm::BasicBlock* predBB);

    void dfsForClosingBrackets(std::set<std::string>& visited, llvm::BasicBlock* bb, std::map<std::string, uint64_t>& closingBrackets);

    llvm::Function& fn;
    udm::FuncInfo funcInfo;
    std::map<std::pair<std::string, std::string>, std::string> expandedInstructions;
    std::shared_ptr<spdlog::logger> logger;
};

}   // namespace codeGen

#endif // _GENERATE_FN_BODY_H_