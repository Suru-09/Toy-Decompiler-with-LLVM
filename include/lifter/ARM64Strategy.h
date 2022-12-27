#ifndef __ARM64_STRATEGY__H
#define __ARM64_STRATEGY__H

#include "IArchitectureStrategy.h"

namespace lifter {

class ARM64Strategy : public IArchitectureStrategy {
public:
    ARM64Strategy() = default;
    void lift(const std::string& file);
};

}   // end of namespace lifter


#endif