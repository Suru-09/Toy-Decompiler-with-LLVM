#include "codeGen/RenameVariables.h"

#include "logger/LoggerManager.h"
#include "utils/CodeGenUtils.h"

codeGen::RenameVariables::RenameVariables(llvm::Function& f)
: fn(f)
{
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}

std::unordered_map<std::string, std::string> codeGen::RenameVariables::rename()
{
    std::unordered_map<std::string, std::string> result;
    uint64_t argIndex = 0;
    for(llvm::BasicBlock& bb: fn)
    {
        for(llvm::Value& inst: bb)
        {
            if(!inst.hasName())
            {
                continue;
            }

            auto instrTypeStr = utils::CodeGenUtils::typeToString(inst.getType());
            auto instrAlias = "var" + std::to_string(argIndex);

            result[inst.getName().str()] = instrAlias;
            inst.setName(instrAlias);
            argIndex++;
        }
    }

    logger->info("Renamed variables size: {}", result.size());
    return result;
}