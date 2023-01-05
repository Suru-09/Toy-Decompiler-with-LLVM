#ifndef __ELFVISITOR__H
#define __ELFVISITOR__H

#include <memory>
#include <iostream>

#include "IVisitor.h"
#include "LifterContext.h"

namespace lifter
{
    
class ELFVisitor: public IVisitor 
{
public:
    ELFVisitor(std::shared_ptr<LifterContext> ctx) 
    : liftContext(ctx) {}
    void visit(std::shared_ptr<ARM64Strategy> arm);
    void visit(std::shared_ptr<X86Strategy> x86);

private:
    std::shared_ptr<LifterContext> liftContext;
};

} // namespac lifter


#endif