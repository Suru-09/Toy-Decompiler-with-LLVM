#ifndef __ARM64_STRATEGY__H
#define __ARM64_STRATEGY__H

#include <memory>

#include "IArchitectureStrategy.h"

namespace lifter {

class IVisitor;

class ARM64Strategy : public IArchitectureStrategy, public std::enable_shared_from_this<ARM64Strategy>
{
public:
    ARM64Strategy() = default;
    void lift(const std::string& file);
    void visit(std::shared_ptr<IVisitor> v);
};

}   // end of namespace lifter


#endif