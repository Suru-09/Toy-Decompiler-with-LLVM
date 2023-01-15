#include "udm/FunctionsAnalysis.h"

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/ErrorOr.h"
#include "llvm/IR/CFG.h"
#include "llvm/Analysis/PostDominators.h"
#include "llvm/IR/Function.h"
#include "llvm/ADT/GraphTraits.h"
#include "llvm/ADT/PostOrderIterator.h"
#include "utils/UdmUtils.h"
#include "udm/Interval.h"

#include <spdlog/spdlog.h>

#include <vector>
#include <iostream>
#include <set>

std::string udm::FunctionsAnalysis::instructionToString(llvm::Instruction &I)
{
   std::string buf;
   llvm::raw_string_ostream os(buf);
   I.print(os);
   os.flush();
   return buf;
}


std::unordered_map<std::string, udm::FuncInfo> udm::FunctionsAnalysis::getFunctionsInfo() const
{
    return functionsInfo;
}