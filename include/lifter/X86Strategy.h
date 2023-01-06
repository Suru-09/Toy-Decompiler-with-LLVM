#ifndef __X86_STRATEGY__H
#define __X86_STRATEGY__H

#include <memory>
#include <llvm/IR/Module.h>
#include <llvm/Support/Error.h>

#include "IArchitectureStrategy.h"

namespace lifter {

class IVisitor;

class X86_64Strategy : public IArchitectureStrategy, public std::enable_shared_from_this<X86_64Strategy>
{
public:
    X86_64Strategy() = default;
    void liftELF(const std::string& file);
    void visit(std::shared_ptr<IVisitor> v);
    std::vector<std::unique_ptr<llvm::Module>> 
        extractSections(
            llvm::ErrorOr<std::shared_ptr<llvm::MemoryBuffer>> memoryBuff
        );
private:
    llvm::LLVMContext context;
};

}   // end of namespace lifter


#endif