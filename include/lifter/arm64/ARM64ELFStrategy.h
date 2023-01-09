#ifndef __ARM64_STRATEGY__H
#define __ARM64_STRATEGY__H

#include <memory>

#include "lifter/IArchitectureStrategy.h"

namespace lifter {

class ARM64ELFStrategy : public IArchitectureStrategy
{
public:
    ARM64ELFStrategy() = default;
    void lift(const std::string& file);
};

}   // end of namespace lifter


#endif