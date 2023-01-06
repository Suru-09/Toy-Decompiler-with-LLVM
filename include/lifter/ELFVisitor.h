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
    ELFVisitor(const std::string& file_path);
    void visit(std::shared_ptr<IArchitectureStrategy> strategy);
private:
    std::string file;
};

} // namespac lifter


#endif