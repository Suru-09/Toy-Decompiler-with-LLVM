#ifndef _CODE_GENERATION_H_
#define _CODE_GENERATION_H_

#include <iostream>
#include <unordered_map>
#include <memory>

#include "udm/FuncInfo.h"

#include "spdlog/spdlog.h"

#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"

#include "codeGen/instructions/Instruction.h"

namespace codeGen {

class CodeGeneration {
public:
    CodeGeneration(const std::string& irFile, std::unordered_map<std::string, udm::FuncInfo> fnInfoMap);
    ~CodeGeneration() = default;
    void generate();
private:
    void processFunction(llvm::Function& f, const udm::FuncInfo& funcInfo);
    std::string generateFnHeader(llvm::Function& f);
    std::string expandInstruction(llvm::Instruction* instr, int numSpaces);
    bool isValueSubstring(const std::string& value);

    std::string irFile;
    std::unordered_map<std::string, udm::FuncInfo> funcInfoMap;
    std::unordered_map<std::string, std::string> decompiledFunctions;
    std::unordered_map<std::string, std::string> instructionMap;
    std::shared_ptr<spdlog::logger> logger;
};

}   // namespace codeGen

#endif