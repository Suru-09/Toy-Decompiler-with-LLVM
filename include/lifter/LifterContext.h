#ifndef __LIFTER_CONTEXT__H
#define __LIFTER_CONTEXT__H

#include <iostream>
#include <memory>

#include "IArchitectureStrategy.h"

namespace lifter {

class LifterContext : public std::enable_shared_from_this<LifterContext>
{
private:
    std::shared_ptr<IArchitectureStrategy> strategy;
    std::string file;
public:
    LifterContext() = delete;
    LifterContext(const std::string& file);
    
    std::string& getFile();
    void setStrategy(std::shared_ptr<IArchitectureStrategy> strategy);
    void executeStrategy();
};

}   // end of namespace lifter

#endif