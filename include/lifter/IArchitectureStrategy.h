#ifndef __ARCHITECTURE_STRATEGY__H
#define __ARCHITECTURE_STRATEGY__H

#include <iostream>
#include <memory>

#include "IVisitor.h"

namespace lifter {

class IArchitectureStrategy {
public:
    virtual void liftELF(const std::string& file) = 0;
    virtual void visit(std::shared_ptr<IVisitor> v) = 0;
    virtual ~IArchitectureStrategy() = default;
};

}   // end of namespace lifter

#endif