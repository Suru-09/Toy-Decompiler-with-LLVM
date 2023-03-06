#include "lifter/ExecutableType.h"

#include <iostream>
#include <memory>

#include <llvm/Object/ObjectFile.h>
#include <llvm/Support/ErrorOr.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Object/Binary.h>

#include "spdlog/spdlog.h"

lifter::ExecutableType::BinaryType lifter::ExecutableType::getBinaryType(const std::string& file_path) {
    using namespace llvm;

    Expected<object::OwningBinary<object::ObjectFile>> expected_binary 
        = object::ObjectFile::createObjectFile(file_path);

    if(auto error = expected_binary.takeError()) {
        spdlog::error("Either the path or the binary is invalid!");
        return lifter::ExecutableType::BinaryType::ERROR;
    }
    
    object::OwningBinary object = std::move(expected_binary.get());
    object::ObjectFile* binary = object.getBinary();

    if(!binary) {
        spdlog::error("The ObjectFile resulted from the path given is invalid!");
        return lifter::ExecutableType::BinaryType::ERROR;
    }

    if(binary->isELF()) {
        return lifter::ExecutableType::BinaryType::ELF;
    }

    return lifter::ExecutableType::BinaryType::ERROR;
}

llvm::Triple::ArchType lifter::ExecutableType::getArchType(const std::string& file_path) {
   using namespace llvm;

    Expected<object::OwningBinary<object::ObjectFile>> expected_binary 
        = object::ObjectFile::createObjectFile(file_path);

    if(auto error = expected_binary.takeError()) {
        spdlog::error("Either the path or the binary is invalid!\n");
        return llvm::Triple::ArchType::UnknownArch;
    }
    
    object::OwningBinary object = std::move(expected_binary.get());
    object::ObjectFile* binary = object.getBinary();

    if(!binary) {
        std::cout << "The ObjectFile resulted from the path given is invalid!\n";
        return llvm::Triple::ArchType::UnknownArch;
    }

    return binary->getArch();
}