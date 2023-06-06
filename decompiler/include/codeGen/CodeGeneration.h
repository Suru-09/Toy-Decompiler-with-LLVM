#ifndef _CODE_GENERATION_H_
#define _CODE_GENERATION_H_

#include <iostream>
#include <unordered_map>
#include <memory>
#include <map>

#include "codeGen/instructions/Instruction.h"
#include "udm/FuncInfo.h"

#include "spdlog/spdlog.h"

#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/BasicBlock.h"
#include "codeGen/ast/LlvmInstructionNode.h"


namespace codeGen {

enum class GeneratedInstrType {
    ALLOCA,
    BINARY_OP,
    RETURN,
    STORE,
    LOAD,
    BRANCH,
    CALL,
    CAST,
    CMP,
    NONE
};

class CodeGeneration {
public:
    CodeGeneration(const std::string& irFile, std::unordered_map<std::string, udm::FuncInfo> fnInfoMap);
    ~CodeGeneration() = default;
    void generate();
private:
    void processFunction(llvm::Function& f, const udm::FuncInfo& funcInfo);
    void fillInstructionNode(llvm::Instruction* instr, std::shared_ptr<ast::LlvmInstructionNode> root);

    // received in c-tor
    std::string irFile;
    std::unordered_map<std::string, udm::FuncInfo> funcInfoMap;

    // logger
    std::shared_ptr<spdlog::logger> logger;

    // result of code generation
    std::unordered_map<std::string, std::string> decompiledFunctions;

    // map of instruction name and its string representation
    // it has side effects generated by fillInstructionMap functions
    std::map<std::string, std::pair<std::string, GeneratedInstrType>> instructionMap;

    const uint64_t MAX_INSTR_SIZE = 150;
};

}   // namespace codeGen

#endif  // _CODE_GENERATION_H_