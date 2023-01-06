#ifndef __X86_STRATEGY__H
#define __X86_STRATEGY__H

#include <memory>

#include "IArchitectureStrategy.h"

namespace lifter {

class IVisitor;

class X86_64Strategy : public IArchitectureStrategy, public std::enable_shared_from_this<X86_64Strategy>
{
public:
    X86_64Strategy() = default;
    void liftELF(const std::string& file);
    void visit(std::shared_ptr<IVisitor> v);
    void extractSection(const std::string& section_name);
};

}   // end of namespace lifter


#endif