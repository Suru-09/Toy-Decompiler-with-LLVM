#include "lifter/x86_64/X86_64ELFStrategy.h"

#include <memory>
#include <iostream>

#include <llvm/Object/ELFObjectFile.h>
#include <llvm/Support/Error.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>

#include <spdlog/spdlog.h>


void lifter::X86_64ELFStrategy::lift(const std::string& file) {
    using namespace llvm;
    spdlog::info("Starting to lift an X86_64 ELF!");
    ErrorOr<std::shared_ptr<MemoryBuffer>> memoryBuff = 
        MemoryBuffer::getFile(file);
    
    if( std::error_code ec = memoryBuff.getError()) {
        spdlog::error("There was an error while opening the file for lifting the ELF!");
        return;
    }

    auto modules = extractSections(memoryBuff);

    spdlog::info("Starting to print the IR");
    spdlog::info("Size of modules: <{}>", modules.size());
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
        spdlog::error("The ELF64LE X86_64 ObjectFile resulted from the path given is invalid!");
        return sectionModules;
    }

    auto sections = elf.get().sections();
    for(const auto& section: sections) {
        

        if(!section.isText()) {
            continue;
        }
        
        spdlog::info("Found a textSection:");
        auto data = (uint8_t *)section.getContents()->data();

        if(section.getRelocatedSection()) {
            auto wtf = section.getRelocatedSection().get();
            data = (uint8_t *)wtf->getContents()->data();

        }

        spdlog::info("Size of data: {}, <{}>", sizeof(data), section.getSize());
    }
    
    return sectionModules;
}

