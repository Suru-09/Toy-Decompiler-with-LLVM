#include "lifter/X86Strategy.h"

#include <memory>
#include <iostream>

#include <llvm/Object/ELFObjectFile.h>
#include <llvm/Support/Error.h>

void lifter::X86_64Strategy::visit(std::shared_ptr<IVisitor> v) {
    v->visit(shared_from_this());
}

void lifter::X86_64Strategy::liftELF(const std::string& file) {
    using namespace llvm;
    std::cout << "Starting to lift an X86_64 ELF!\n";

    ErrorOr<std::shared_ptr<MemoryBuffer>> memoryBuff = 
        MemoryBuffer::getFile(file);
    
    if( std::error_code ec = memoryBuff.getError()) {
        std::cout << "There was an error while opening the file for lifting the ELF!\n";
        return;
    }

    auto& ref = (*memoryBuff.get().get());
    auto memoryBuffRef = MemoryBufferRef{ref};

    Expected<object::ELFObjectFile<object::ELF64LE>> elf =
      object::ELFObjectFile<object::ELF64LE>::create(memoryBuffRef);
    
    if(auto error = elf.takeError()) {
        std::cout << "The ELF64LE X86_64 ObjectFile resulted from the path given is invalid!\n";
        return;
    }

    auto sections = elf.get().sections();
    for(const auto& section: sections) {
        if(section.isText()) {
            std::cout << "Found a textSection!\n";
        }
    }
}


void lifter::X86_64Strategy::extractSection(const std::string& section_name) {

}