#include <iostream>
#include <memory>

#include "lifter/IArchitectureStrategy.h"
#include "lifter/LifterContext.h"
#include "lifter/X86Strategy.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FileSystem.h>
#include <capstone/capstone.h>


int main(int argc, char** argv) {
    std::shared_ptr<lifter::LifterContext> lifterCtx =  
      std::make_shared<lifter::LifterContext>(lifter::LifterContext{"../test/test.exe"});
    std::shared_ptr<lifter::IArchitectureStrategy> strategy = std::make_unique<lifter::X86Strategy>();

    lifterCtx->setStrategy(std::move(strategy));
    lifterCtx->executeStrategy();

    if(!strategy) {
        std::cout << "Strategy is null after beeing moved\n";
    }
    else {
        std::cout << "Strategy is NOT null after beeing moved\n";
    }

    return 0;
}