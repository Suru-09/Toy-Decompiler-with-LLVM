#include "lifter/X86_64ELFStrategy.h"

#include <memory>
#include <iostream>

#include <llvm/Object/ELFObjectFile.h>
#include <llvm/Support/Error.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/raw_ostream.h>


void lifter::X86_64ELFStrategy::lift(const std::string& file) {
    using namespace llvm;
    std::cout << "Starting to lift an X86_64 ELF!\n";
    ErrorOr<std::shared_ptr<MemoryBuffer>> memoryBuff = 
        MemoryBuffer::getFile(file);
    
    if( std::error_code ec = memoryBuff.getError()) {
        std::cout << "There was an error while opening the file for lifting the ELF!\n";
        return;
    }

    auto modules = extractSections(memoryBuff);

    std::cout << "Starting to print the IR\n";
    std::cout << "Size of modules: <" << modules.size() << ">\n";
    for(const auto& m: modules) {
        m->print(outs(), nullptr);
    }
}


std::vector<std::unique_ptr<llvm::Module>> 
    lifter::X86_64ELFStrategy::extractSections(
        llvm::ErrorOr<std::shared_ptr<llvm::MemoryBuffer>> memoryBuff) 
{
    using namespace llvm;
    std::vector<std::unique_ptr<Module>> sectionModules;

    auto& ref = (*memoryBuff.get().get());
    auto memoryBuffRef = MemoryBufferRef{ref};

    Expected<object::ELFObjectFile<object::ELF64LE>> elf =
      object::ELFObjectFile<object::ELF64LE>::create(memoryBuffRef);
    
    if(auto error = elf.takeError()) {
        std::cout << "The ELF64LE X86_64 ObjectFile resulted from the path given is invalid!\n";
        return sectionModules;
    }

    auto sections = elf.get().sections();
    for(const auto& section: sections) {
        if(section.isText()) {
            std::cout << "Found a textSection!\n";
        }

        StringRef contents;
        if (auto ec = section.getContents().takeError()) {
            std::cout << "The ELF64LE X86_64 ObjectFile resulted from the path given is invalid!\n";
            return sectionModules;
        }

        SMDiagnostic err;
        MemoryBufferRef refMem{section.getContents().get(), "my_section"};
        std::unique_ptr<Module> sectModule = parseIR(refMem, err ,context);
        if(sectModule) {
        sectionModules.push_back(std::move(sectModule));
        }
        else {
            std::cout << err.getMessage().str() << "\n";
        }
    }
    
    return sectionModules;
}