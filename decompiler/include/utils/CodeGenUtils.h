#ifndef _CODE_GEN_UTILS_H_
#define _CODE_GEN_UTILS_H_

#include <iostream>

#include "llvm/IR/Type.h"

namespace utils
{

class CodeGenUtils
{
public:
    static std::string getSpaces(int numSpaces);
    static std::string typeToString(llvm::Type* type);
};

}   // namespace utils

#endif