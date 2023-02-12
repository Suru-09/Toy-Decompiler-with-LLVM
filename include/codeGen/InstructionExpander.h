#ifndef _INSTRUCTION_EXPANDER_H_
#define _INSTRUCTION_EXPANDER_H_

#include <iostream>
#include <map>

#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>

#include <spdlog/spdlog.h>

namespace codeGen {

class InstructionExpander {
public:
    InstructionExpander(llvm::Function *f);
    std::map<std::pair<std::string, std::string>, std::string> getExpandedInstructions();
private:
    void initExpandedInstructions();
    std::string expandInstruction(llvm::Instruction *inst, int64_t offset);

    llvm::Function& fn;
    /**
     * @brief The map of expanded instructions is important to note. 
     * The key is a pair of the basic block name and the instruction name,
     * whereas the value is the expanded instruction.
     */
    std::map<std::pair<std::string, std::string>, std::string> expandedInstructions;
    std::shared_ptr<spdlog::logger> logger;
};

}   // namespace codeGen 


#endif // _INSTRUCTION_EXPANDER_H_