#include "codeGen/GenerateFnHeader.h"

#include "utils/CodeGenUtils.h"
#include "logger/LoggerManager.h"


codeGen::GenerateFnHeader::GenerateFnHeader(llvm::Function& f)
: fn(f)
{
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}

std::string codeGen::GenerateFnHeader::generate()
{
    std::string result = "";
    result += "Fn " + fn.getName().str() + "(";
    
    bool isCommaNeeded = true;
    uint64_t argCount = fn.arg_size(), argIndex = 0;
    for(auto& arg: fn.args())
    {
        std::string argType = utils::CodeGenUtils::typeToString(arg.getType());
        result += arg.getName().str() + ": " + argType;
        if(argIndex < argCount - 1)
        {
            result += ", ";
        }
        argIndex++;
    }

    std::string returnType = utils::CodeGenUtils::typeToString(fn.getReturnType());
    result += ") -> " + returnType + "\n{\n";

    logger->info("Function header: {}", result);
    return result;
}