#ifndef REVERSE_ENGINEERING_TOOL_DEFINEVARIABLES_H
#define REVERSE_ENGINEERING_TOOL_DEFINEVARIABLES_H

#include <string>
#include <memory>
#include <map>
#include <llvm/IR/Function.h>
#include <spdlog/spdlog.h>

#include "codeGen/Variable.h"

namespace codeGen {

/**
 * @brief The purpose of this class is to define the local, stack variables at beginning
 * of a function.
 * @details the handle() method will return a map containing as key the name of the variable,
 * and as value an object defining the type, initial value of the variable.
 */
class DefineVariablesHandler {
public:
    explicit DefineVariablesHandler(llvm::Function &llvmFn);
    ~DefineVariablesHandler() = default;

    std::map<std::string, std::vector<codeGen::Variable>>  handle();
private:
    llvm::Function& llvmFn;
    std::map<std::string, std::vector<codeGen::Variable>> variables;
    std::shared_ptr<spdlog::logger> logger;

    std::string getVariableInitialValue(const llvm::Instruction& instr);
};


}   // namespace codeGen

#endif //REVERSE_ENGINEERING_TOOL_DEFINEVARIABLES_H
