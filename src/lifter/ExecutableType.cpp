#include "lifter/ExecutableType.h"

#include <iostream>
#include <memory>

#include "llvm/Object/ObjectFile.h"
#include "llvm/Support/ErrorOr.h"
#include "llvm/Support/FileSystem.h"

lifter::ExecutableType::BinaryType lifter::ExecutableType::getBinaryType(const std::string& file_path) {
    using namespace llvm;

    Expected<object::OwningBinary<object::ObjectFile>> expected_binary 
        = object::ObjectFile::createObjectFile(file_path);
    
    object::OwningBinary object = std::move(expected_binary.get());

    // if(object.errorIsA()) {
    //     std::cout << "The given file is not good!\n";
    //     return lifter::ExecutableType::BinaryType::ERROR;
    // }
    object::ObjectFile* binary = object.getBinary();
    std::cout << "Found value: [" << binary->getType() << "]\n";

    return lifter::ExecutableType::BinaryType::ELF;
}