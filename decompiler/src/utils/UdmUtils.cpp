#include "utils/UdmUtils.h"

#include <llvm/IR/CFG.h>


std::vector<std::string> utils::UdmUtils::getPredecessors(llvm::BasicBlock* bb)
{
    std::vector<std::string> predecessors;
    for(auto pred: llvm::predecessors(bb))
    {
        predecessors.emplace_back(pred->getName());
    }

    return predecessors;
}

std::vector<std::string> utils::UdmUtils::getSuccessors(llvm::BasicBlock* bb)
{
    std::vector<std::string> successors;
    for(auto succ: llvm::successors(bb))
    {
        successors.emplace_back(succ->getName());
    }

    return successors;
}