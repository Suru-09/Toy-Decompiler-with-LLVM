#include "codeGen/RenameVariables.h"

#include "logger/LoggerManager.h"
#include "utils/CodeGenUtils.h"

#include <llvm/IR/Instructions.h>

codeGen::RenameVariables::RenameVariables(llvm::Function& f)
: fn(f)
{
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
    typesMap = std::unordered_map<VariableType, std::pair<std::string, unsigned int>>{
            {RenameVariables::VariableType::ARG,    {"arg_",    0}},
            {RenameVariables::VariableType::LOCAL,  {"lvar_",   0}},
            {RenameVariables::VariableType::STACK,  {"svar_",   0}},
            {RenameVariables::VariableType::GLOBAL, {"global_", 0}},
            {RenameVariables::VariableType::RETURN_VALUE, {"ret_val_", 0}},
    };
}

std::unordered_map<std::string, std::string> codeGen::RenameVariables::rename()
{
    std::unordered_map<std::string, std::string> result;
    for(llvm::BasicBlock& bb: fn)
    {
        for(llvm::Value& inst: bb)
        {
            if(!inst.hasName())
            {
                continue;
            }

//            if( auto* retInst = llvm::dyn_cast<llvm::ReturnInst>(&inst) )
//            {
//                auto instrType = RenameVariables::VariableType::RETURN_VALUE;
//                auto instrAlias = typesMap[instrType].first + std::to_string(typesMap[instrType].second);
//                inst.setName(instrAlias);
//                typesMap[instrType].second++;
//                continue;
//            }

            // check if instruction is a phi node
            if( auto* phiNode =  llvm::dyn_cast<llvm::PHINode>(&inst))
            {
                auto instrType = RenameVariables::VariableType::STACK;
                auto instrAlias = typesMap[instrType].first + std::to_string(typesMap[instrType].second);
                inst.setName(instrAlias);
                typesMap[instrType].second++;
                continue;
            }

            auto instrType = RenameVariables::VariableType::LOCAL;
            auto instrAlias = typesMap[instrType].first + std::to_string(typesMap[instrType].second);
            inst.setName(instrAlias);
            typesMap[instrType].second++;
        }
    }

    logger->info("Renamed variables size: {}", result.size());
    return result;
}