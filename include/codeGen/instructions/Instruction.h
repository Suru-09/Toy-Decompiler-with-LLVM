#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include <iostream>
#include <memory>

#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>

#include "spdlog/spdlog.h"


namespace codeGen {

class Instruction {
public:
    explicit Instruction();
    ~Instruction() = default;

    virtual std::string toString() = 0;
    static std::shared_ptr<Instruction> getInstruction(llvm::Instruction& inst);
protected:
    std::string instructionString;
    std::shared_ptr<spdlog::logger> logger;
};

}  // namespace codeGen


#endif