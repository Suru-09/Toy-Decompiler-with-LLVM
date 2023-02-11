#ifndef _GENERATE_FN_HEADER_H_
#define _GENERATE_FN_HEADER_H_

#include <iostream>

#include <llvm/IR/Function.h>

#include <spdlog/spdlog.h>

namespace codeGen {

class GenerateFnHeader {
public:
    explicit GenerateFnHeader(llvm::Function& f);
    ~GenerateFnHeader() = default;

    std::string generate();
private:
    llvm::Function& fn;
    std::shared_ptr<spdlog::logger> logger;
};

}   // namespace codeGen

#endif // _GENERATE_FN_HEADER_H_