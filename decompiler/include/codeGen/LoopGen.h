#ifndef __LOOP_GEN_H__
#define __LOOP_GEN_H__

#include <iostream>

#include "codeGen/instructions/Instruction.h"
#include "udm/BBInfo.h"

namespace codeGen {

class LoopGen {
public:
    LoopGen() = default;
    ~LoopGen() = default;

    static std::string generateLoop(const std::string& condition, int numSpaces, udm::BBInfo::LoopType loopType);
};

}   // namespace codeGen

#endif