#ifndef __X86_STRATEGY__H
#define __X86_STRATEGY__H

#include "IArchitectureStrategy.h"

namespace lifter {

class X86Strategy : public IArchitectureStrategy {
public:
    X86Strategy() = default;
    void lift(const std::string& file);
};

}   // end of namespace lifter


#endif