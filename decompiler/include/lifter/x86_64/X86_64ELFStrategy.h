#ifndef __X86_STRATEGY__H
#define __X86_STRATEGY__H

#include <memory>

#include <spdlog/spdlog.h>

#include "lifter/IArchitectureStrategy.h"

namespace lifter {


class X86_64ELFStrategy : public IArchitectureStrategy
{
public:
    explicit X86_64ELFStrategy();
    void lift(const std::string& file);
private:
    std::shared_ptr<spdlog::logger> logger;
};

}   // end of namespace lifter


#endif