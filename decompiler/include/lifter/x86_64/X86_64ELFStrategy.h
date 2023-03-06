#ifndef __X86_STRATEGY__H
#define __X86_STRATEGY__H

#include <memory>
#include <llvm/IR/Module.h>
#include <llvm/Support/Error.h>

#include "lifter/IArchitectureStrategy.h"

namespace lifter {


class X86_64ELFStrategy : public IArchitectureStrategy
{
public:
    X86_64ELFStrategy() = default;
    void lift(const std::string& file);
    std::vector<std::unique_ptr<llvm::Module>> 
        extractSections(
            llvm::ErrorOr<std::shared_ptr<llvm::MemoryBuffer>> memoryBuff
        );
private:
    llvm::LLVMContext context;
};

}   // end of namespace lifter


#endif