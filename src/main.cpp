#include <iostream>
#include <memory>

// #include "lifter/IArchitectureStrategy.h"
// #include "lifter/LifterContext.h"
// #include "lifter/ARM64Strategy.h"

// int main(int argc, char** argv) {
    
//     lifter::LifterContext lifterCtx = lifter::LifterContext{"test.o"};
//     std::unique_ptr<lifter::IArchitectureStrategy> strategy = std::make_unique<lifter::ARM64Strategy>();
//     lifterCtx.setStrategy(std::move(strategy));

//     lifterCtx.executeStrategy();

//     if(!strategy) {
//         std::cout << "Strategy is null after beeing moved\n";
//     }
//     else {
//        std::cout << "Strategy is NOT null after beeing moved\n";
//     }
//     return 0;
// }

/*
#include <iostream>
#include <capstone/capstone.h>

int main() {
  // Initialize the Capstone engine
  csh handle;
  if (cs_open(CS_ARCH_ARM64, CS_MODE_ARM, &handle) != CS_ERR_OK) {
    std::cerr << "Error: Unable to initialize Capstone" << std::endl;
    return 1;
  }

  // Define the code to disassemble
  uint8_t code[] = {
    0x21, 0x7c, 0x02, 0x9b, 0x21, 0x7c, 0x00, 0x53,
    0x00, 0x40, 0x21, 0x4b, 0xe1, 0x0b, 0x40, 0xb9,
    0x20, 0x04, 0x81, 0xda, 0x20, 0x08, 0x02, 0x8b
  };
  size_t code_size = sizeof(code);

  // Disassemble the code
  cs_insn* insn;
  size_t count = cs_disasm(handle, code, code_size, 0, 0, &insn);
  if (count > 0) {
    // Disassembly successful
    for (size_t i = 0; i < count; i++) {
      std::cout << insn[i].mnemonic << " " << insn[i].op_str << std::endl;
    }

    // Free the disassembled instructions
    cs_free(insn, count);
  } else {
    // Error disassembling code
    std::cerr << "Error: Unable to disassemble code\n";
  }
  return 0;
}
*/


#include <capstone/capstone.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FileSystem.h>


int main() {
  // Initialize the Capstone disassembler
  csh handle;
  cs_err err = cs_open(CS_ARCH_X86, CS_MODE_64, &handle);
  if (err != CS_ERR_OK) {
    // Handle error
  }

  // Disassemble some x86 instructions
  uint8_t code[] = {
    0x48, 0x83, 0xec, 0x20, // sub rsp, 0x20
    0x48, 0x8b, 0x05, 0x01, 0x00, 0x00, 0x00, // mov rax, [rip+1]
    0xc3 // ret
  };
  cs_insn *insn;
  size_t count = cs_disasm(handle, code, sizeof(code), 0x1000, 0, &insn);
  if (count > 0) {
    // Iterate over the disassembled instructions
    for (size_t i = 0; i < count; i++) {
      printf("%s\n", insn[i].mnemonic);
    }

    // Free the disassembled instructions
    cs_free(insn, count);
  } else {
    // Handle
  }
  return 0;
}