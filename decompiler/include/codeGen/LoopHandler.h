#ifndef __LOOP_GEN_H__
#define __LOOP_GEN_H__

#include <iostream>

#include "codeGen/instructions/Instruction.h"
#include "udm/BBInfo.h"

namespace codeGen {

class LoopHandler {
public:
    LoopHandler() = default;
    ~LoopHandler() = default;

    static std::string generateLoop(const std::string& condition, int numSpaces, udm::BBInfo::LoopType loopType);
};

}   // namespace codeGen

#endif