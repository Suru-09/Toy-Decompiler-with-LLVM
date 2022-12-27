#ifndef __ARCHITECTURE_STRATEGY__H
#define __ARCHITECTURE_STRATEGY__H

#include <iostream>

namespace lifter {

class IArchitectureStrategy {
public:
    virtual void lift(const std::string& file) = 0;
    virtual ~IArchitectureStrategy() = default;
};

}   // end of namespace lifter

#endif