#include "lifter/x86_64/X86_64ELFStrategy.h"

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

#include <spdlog/spdlog.h>
#include <capstone/capstone.h>


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

        csh handle;
        cs_err error = cs_open(CS_ARCH_X86, CS_MODE_64, &handle);
        cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);
        if (error != CS_ERR_OK) {
            spdlog::error("Error from capstone");
        }

        auto addressToStart = section.getAddress();
        cs_insn *insn;
        size_t count = cs_disasm(handle, data, sizeof(data), addressToStart, 0, &insn);
        if (count > 0) {
            // Iterate over the disassembled instructions
            for (size_t j = 0; j < count; j++) {
                // printf( "0x%"PRIx64":\t%s\t\t%s\n", insn[j].address, insn[j].mnemonic,
                //         insn[j].op_str);
            }

            // Free the disassembled instructions
            cs_free(insn, count);
        } else {
            // Handle
        }
    }
    
    return sectionModules;
}

