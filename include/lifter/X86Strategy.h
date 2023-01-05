#ifndef __X86_STRATEGY__H
#define __X86_STRATEGY__H

#include <memory>

#include "IArchitectureStrategy.h"

namespace lifter {

class IVisitor;

class X86Strategy : public IArchitectureStrategy, public std::enable_shared_from_this<X86Strategy>
{
public:
    X86Strategy() = default;
    void lift(const std::string& file);
    void visit(std::shared_ptr<IVisitor> v);
};

}   // end of namespace lifter


#endif