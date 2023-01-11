#include <iostream>
#include <memory>

#include "utils/LifterUtils.h"

#include "spdlog/spdlog.h"

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/ErrorOr.h"

std::string instructionToString(llvm::Instruction &I) {
   std::string buf;
   llvm::raw_string_ostream os(buf);
   I.print(os);
   os.flush();
   return buf;
}

int main(int argc, char** argv) {
   std::string testing_file = "../testing_files/elfC/fibbo_c";

   std::shared_ptr<lifter::LifterContext> lifterCtx = utils::getLifterCtx(testing_file);

   if(!lifterCtx)
   {
      spdlog::critical("Invalid lifterContext created(nullptr)!");
      exit(1);
   }
      
      //lifterCtx->executeStrategy();
      std::string llvmIRFile = testing_file + ".ll";
      llvm::LLVMContext context;
      llvm::SMDiagnostic error;

      std::unique_ptr<llvm::Module> mod = llvm::parseIRFile(llvmIRFile, error, context);

      if (!mod) {
         spdlog::critical("Couldn't open the file with LLVM IR!");
         return 1;
      }

      for(llvm::Function &f: mod->functions())
      {
         spdlog::info("Functio name: {}", f.getName());
         for (llvm::BasicBlock &BB : f) {
            for (llvm::Instruction &I : BB) {
               // Do something with the instruction, e.g., printing its opcode
               spdlog::info("Instruction: {}", instructionToString(I));
            }
         }
      }
      return 0;
}