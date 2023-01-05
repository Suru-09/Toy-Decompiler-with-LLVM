#ifndef __VISITOR_FACTORY__H
#define __VISITOR_FACTORY__H

#include "IVisitor.h"
#include "ExecutableType.h"
#include "LifterContext.h"

#include <llvm/Object/Binary.h>

#include <memory>

namespace lifter
{

class VisitorFactory {
public:
    VisitorFactory() = delete;
    VisitorFactory(std::shared_ptr<LifterContext> lifter);
    std::shared_ptr<IVisitor> createVisitor(lifter::ExecutableType::BinaryType binType);
private:
    std::shared_ptr<LifterContext> lifterContext;
};

} // namespace lifter


#endif