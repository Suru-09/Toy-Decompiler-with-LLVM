#ifndef __LIFTER_CONTEXT__H
#define __LIFTER_CONTEXT__H

#include <iostream>
#include <memory>

#include "IArchitectureStrategy.h"

namespace lifter {

class LifterContext
{
private:
    std::shared_ptr<IArchitectureStrategy> strategy;
    std::string file;
public:
    explicit LifterContext();
    ~LifterContext() = default;
    
    void setStrategy(std::shared_ptr<IArchitectureStrategy> strategy);
    void executeStrategy();
};

}   // end of namespace lifter

#endif