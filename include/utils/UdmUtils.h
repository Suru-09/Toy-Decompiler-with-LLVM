#ifndef __UDM_UTILS__H
#define __UDM_UTILS__H

#include <iostream>
#include <vector>

#include <llvm/IR/BasicBlock.h>


namespace utils {

class UdmUtils {
public:
    static std::vector<std::string> getPredecessors(llvm::BasicBlock* bb);
    static std::vector<std::string> getSuccessors(llvm::BasicBlock* bb);
};

} // utils

#endif // __UDM_UTILS__H
