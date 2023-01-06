#ifndef __IVISITOR__H
#define __IVISITOR__H

#include <memory>
#include <iostream>

namespace lifter
{

class IArchitectureStrategy;
    
class IVisitor {
public:
    virtual void visit(std::shared_ptr<IArchitectureStrategy> strategy) = 0;
};

} // namespac lifter


#endif