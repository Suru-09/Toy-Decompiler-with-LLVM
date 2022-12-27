#ifndef __LIFTER_CONTEXT__H
#define __LIFTER_CONTEXT__H

#include <iostream>
#include <memory>

#include "IArchitectureStrategy.h"

namespace lifter {

class LifterContext {
private:
    std::unique_ptr<IArchitectureStrategy> strategy;
    std::string file;
public:
    LifterContext() = delete;
    LifterContext(const std::string& file);
    
    void setStrategy(std::unique_ptr<IArchitectureStrategy> strategy);
    void executeStrategy();
};

}   // end of namespace lifter

#endif