#ifndef _RENAME_VARIABLES_H_
#define _RENAME_VARIABLES_H_

#include <iostream>
#include <unordered_map>

#include <llvm/IR/Function.h>

#include <spdlog/spdlog.h>

namespace codeGen {

class RenameVariables {
public:
    explicit RenameVariables(llvm::Function& f);
    ~RenameVariables() = default;

    enum class VariableType {
        ARG,
        LOCAL,
        STACK,
        GLOBAL,
        RETURN_VALUE,
        NONE
    };

    /**
     * @brief Rename variables in function based on their type and index.
     * @return std::unordered_map<std::string, std::string> map of alises for the
     * initial variable names
     */
    std::unordered_map<std::string, std::string> rename();

private:
    llvm::Function& fn;
    // Map of initial variable names to their aliases
    std::unordered_map<std::string, std::string> aliasesMap;
    std::unordered_map<VariableType, std::pair<std::string, unsigned int>> typesMap;
    std::shared_ptr<spdlog::logger> logger;
};

}   // namespace codeGen


#endif // _RENAME_VARIABLES_H_