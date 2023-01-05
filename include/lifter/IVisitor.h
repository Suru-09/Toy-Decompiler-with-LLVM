#ifndef __IVISITOR__H
#define __IVISITOR__H

#include <memory>
#include <iostream>

namespace lifter
{

class ARM64Strategy;
class X86Strategy;
    
class IVisitor {
public:
    virtual void visit(std::shared_ptr<ARM64Strategy> arm) = 0;
    virtual void visit(std::shared_ptr<X86Strategy> x86) = 0;
};

} // namespac lifter


#endif