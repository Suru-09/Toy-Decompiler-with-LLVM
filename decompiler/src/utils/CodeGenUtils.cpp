#include <llvm/IR/Instructions.h>
#include <regex>

#include "utils/CodeGenUtils.h"
#include "codeGen/instructions/Instruction.h"
#include "codeGen/ast/PHINodeHandler.h"

#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"
#include <llvm/IR/Value.h>
#include "llvm/IR/Type.h"
#include "llvm/Support/Casting.h"

std::string utils::CodeGenUtils::getSpaces(int numSpaces)
{
   std::string result = "";
   for(int i = 0; i < numSpaces; i++)
   {
      result += " ";
   }
   return result;
}

/* ! PROTOTYPE for TypeID from llvm 17.0

enum TypeID {
     // PrimitiveTypes
     HalfTyID = 0,  ///< 16-bit floating point type
     BFloatTyID,    ///< 16-bit floating point type (7-bit significand)
     FloatTyID,     ///< 32-bit floating point type
     DoubleTyID,    ///< 64-bit floating point type
     X86_FP80TyID,  ///< 80-bit floating point type (X87)
     FP128TyID,     ///< 128-bit floating point type (112-bit significand)
     PPC_FP128TyID, ///< 128-bit floating point type (two 64-bits, PowerPC)
     VoidTyID,      ///< type with no size
     LabelTyID,     ///< Labels
     MetadataTyID,  ///< Metadata
     X86_MMXTyID,   ///< MMX vectors (64 bits, X86 specific)
     X86_AMXTyID,   ///< AMX vectors (8192 bits, X86 specific)
     TokenTyID,     ///< Tokens
  
     // Derived types... see DerivedTypes.h file.
     IntegerTyID,        ///< Arbitrary bit width integers
     FunctionTyID,       ///< Functions
     PointerTyID,        ///< Pointers
     StructTyID,         ///< Structures
     ArrayTyID,          ///< Arrays
     FixedVectorTyID,    ///< Fixed width SIMD vector type
     ScalableVectorTyID, ///< Scalable SIMD vector type
     TypedPointerTyID,   ///< Typed pointer used by some GPU targets
     TargetExtTyID,      ///< Target extension type
   };
*/

std::string utils::CodeGenUtils::typeToString(llvm::Type* type)
{
    if(type->isVoidTy())
        return "void";
    
    if(type->isIntegerTy())
    {
        llvm::IntegerType* intType = llvm::dyn_cast<llvm::IntegerType>(type);
        std::size_t bitWidth = intType->getBitWidth();
        if(bitWidth == 1)
            return "bool";
        return "i" + std::to_string(intType->getBitWidth());
    }

    if(type->isBFloatTy())
        return "bfloat";

    if(type->isHalfTy() && type->isFloatTy())
        return "half_float";

    if(type->isFloatTy())
        return "f32";
    
    if(type->isDoubleTy())
        return "f64";
    
    if(type->isX86_FP80Ty())
        return "f80";
    
    if(type->isFP128Ty())
        return "f128";
    
    if(type->isPPC_FP128Ty())
        return "ppc_f128";
    
    if(type->isArrayTy())
    {
        llvm::ArrayType* arrayType = llvm::dyn_cast<llvm::ArrayType>(type);
        return "array::" + typeToString(arrayType->getElementType()) + "[" + std::to_string(arrayType->getNumElements()) + "]";
    }

    if(type->isStructTy())
    {
        llvm::StructType* structType = llvm::dyn_cast<llvm::StructType>(type);
        std::string result = "struct::";
        result += type->getStructName().str() + "(";
        for(int i = 0; i < structType->getNumElements(); i++)
        {
            result += typeToString(structType->getElementType(i));
            if(i != structType->getNumElements() - 1)
                result += ", ";
        }
        result += ")";
        return result;
    }

    if(type->isPointerTy())
    {
        llvm::PointerType* pointerType = llvm::dyn_cast<llvm::PointerType>(type);
        return "ptr::" + typeToString(pointerType->getContainedType(0));
    }


    if(type->isFunctionTy())
    {
        llvm::FunctionType* funcType = llvm::dyn_cast<llvm::FunctionType>(type);
        std::string result = "func::(";
        result += typeToString(funcType->getReturnType()) + ")(";
        for(int i = 0; i < funcType->getNumParams(); i++)
        {
            result += typeToString(funcType->getParamType(i));
            if(i != funcType->getNumParams() - 1)
                result += ", ";
        }
        result += ")";
    }

    return "NULL";
}

bool utils::CodeGenUtils::canAssignTo(llvm::Instruction *instr) {
    const unsigned int opCode = instr->getOpcode();
    switch (opCode)
    {
        case llvm::Instruction::Br:
        case llvm::Instruction::Ret:
        case llvm::Instruction::Switch:
        case llvm::Instruction::IndirectBr:
        case llvm::Instruction::Store:
            return false;
        default:
            return true;
    }
    return false;
}

std::vector<std::string> utils::CodeGenUtils::extractSubstrings(const std::string& input, const std::string& subStr)
{
    // create regex pattern for finding substrings
    std::string pattern = "\\[" + subStr + R"(:\s*\{([^\}]+)\}\])";
    std::regex re(pattern);

    // find all matches and store in a vector
    std::vector<std::string> matches;
    std::smatch sm;
    std::string::const_iterator it(input.cbegin());
    std::string::const_iterator end(input.cend());
    while (std::regex_search(it, end, sm, re)) {
        matches.push_back(sm[1].str());
        it = sm.suffix().first;
    }

    return matches;
}

std::vector<std::string> utils::CodeGenUtils::extractValuesFromPhiString(const std::string &phiString) {
    std::vector<std::string> values;
    size_t startPos = phiString.find("value:{");
    startPos += 7;
    size_t endPos = phiString.find('}', startPos);
    if (endPos == std::string::npos || startPos == std::string::npos)
        return values;
    values.push_back(phiString.substr(startPos, endPos - startPos));
    while((startPos = phiString.find("value:{", endPos)) != std::string::npos)
    {
        startPos += 7;
        endPos = phiString.find('}', startPos);
        if (endPos == std::string::npos || startPos == std::string::npos)
            break;
        values.push_back(phiString.substr(startPos, endPos - startPos));
    }
    // add last value
    return values;
}

std::vector<std::string> utils::CodeGenUtils::extractLabelsFromPhiString(const std::string &phiString) {
    std::vector<std::string> labels;
    std::string findAfter = "label:{";
    std::size_t searchedLen = findAfter.length();
    size_t startPos = phiString.find("label:{") + searchedLen;
    size_t endPos = phiString.find('}', startPos);
    if (endPos == std::string::npos || startPos == std::string::npos)
        return labels;
    labels.push_back(phiString.substr(startPos, endPos - startPos));
    while((startPos = phiString.find("label:{", endPos)) != std::string::npos)
    {
        startPos += searchedLen;
        endPos = phiString.find('}', startPos);
        if (endPos == std::string::npos || startPos == std::string::npos)
            break;
        labels.push_back(phiString.substr(startPos, endPos - startPos));
    }
    return labels;
}

std::string utils::CodeGenUtils::extractPhiNodeLeftValue(const std::string &phiString) {
    size_t startPos = phiString.find('=');
    return phiString.substr(0, startPos);
}

bool utils::CodeGenUtils::isLoop(const udm::FuncInfo& funcInfo, const std::string& bbLabel)
{
    auto bbInfo = funcInfo.getBBInfo(bbLabel);
    return bbInfo.getIsLoop() && bbInfo.getLoopType() != udm::BBInfo::LoopType::NONE;
}

std::pair<std::string, std::string> utils::CodeGenUtils::getTerminatorCondition(llvm::Function &func, const std::string &bbLabel) {
    auto extractValueFromTerminator = [](llvm::Instruction* terminator) -> std::string
    {
        if(auto branchInstr = llvm::dyn_cast<llvm::BranchInst>(terminator))
        {
            if(branchInstr->isConditional())
            {
                spdlog::error("Found conditional jump in bb: {}, with value: {}", llvmValueToString(branchInstr->getCondition()));
                return llvmValueToString(branchInstr->getCondition());
            }
        }
        return std::string{};
    };

    for(auto& bb : func)
    {
        if(bb.getName().str() != bbLabel)
        {
            continue;
        }


        auto terminator = bb.getTerminator();
        // if terminator has 2 successors, it is a conditional jump(might be a loop/if).
        // if it is an unconditional jump we don't care about it and return empty string
        auto branchCondition = std::make_pair(bb.getName().str(), extractValueFromTerminator(terminator));
        // in this case for a while loop we might an optimization with an empty preheader
        // so will we will check the next bb and see if we have the loop body.
        if(branchCondition.second.empty())
        {
            auto nextBB = bb.getNextNode();
            if(nextBB == nullptr)
            {
                spdlog::error("Could not find next bb for bb: {}", bbLabel);
                return std::pair<std::string, std::string>{};
            }
            auto nextBBTerminator = nextBB->getTerminator();
            branchCondition = std::make_pair(nextBB->getName().str(), extractValueFromTerminator(nextBBTerminator));
        }
        return branchCondition;
    }
    return std::pair<std::string, std::string>{};
}

std::string utils::CodeGenUtils::getInstructionValue(const llvm::Instruction *instr) {
    std::string value;

    if(instr->hasName())
    {
        return instr->getName().str();
    }
    // check if constant (int, float, string, etc.)
    if(instr->getOpcode() == llvm::Instruction::ConstantFPVal)
    {
        auto constant = llvm::dyn_cast<llvm::ConstantFP>(instr);
        value = std::to_string(constant->getValueAPF().convertToFloat());
    }
    else if(instr->getOpcode() == llvm::Instruction::ConstantIntVal)
    {
        auto constant = llvm::dyn_cast<llvm::ConstantInt>(instr);
        value = std::to_string(constant->getSExtValue());
    }
    else if(instr->getOpcode() == llvm::Instruction::ConstantDataArrayVal)
    {
        auto constant = llvm::dyn_cast<llvm::ConstantDataArray>(instr);
        value = constant->getAsString().str();
    }
    else if(instr->getOpcode() == llvm::Instruction::ConstantDataVectorVal)
    {
        auto constant = llvm::dyn_cast<llvm::ConstantDataVector>(instr);
        value = constant->getAsString().str();
    }

    return value;
}

std::string utils::CodeGenUtils::llvmValueToString(llvm::Value *value) {
    auto llvmValueToString = [](llvm::Value* value){
        std::string str;
        if(auto* constInt = llvm::dyn_cast<llvm::ConstantInt>(value))
        {
            str += std::to_string(constInt->getSExtValue());
        }
        else if(auto* constFP = llvm::dyn_cast<llvm::ConstantFP>(value))
        {
            str += std::to_string(constFP->getValueAPF().convertToDouble());
        }
        else
        {
            str += value->getName().str();
        }
        return str;
    };
    return llvmValueToString(value);
}


bool utils::CodeGenUtils::doesInstructionHaveSingleUse(const llvm::Instruction *instr) {
    return instr->hasOneUse();
}

llvm::BasicBlock *utils::CodeGenUtils::getBBAfterLabel(llvm::Function &func, const std::string &bbLabel) {
    for(auto& bb : func)
    {
        if(bb.getName() == bbLabel)
            return &bb;
    }
    return nullptr;
}

llvm::Instruction *utils::CodeGenUtils::getInstructionAfterLabel(llvm::Function &func, const std::string &instrLabel) {
    for(auto& bb : func)
    {
        for(auto& instr : bb)
        {
            if(instr.getName() == instrLabel)
            {
                return &instr;
            }
        }
    }
    return nullptr;
}

std::string utils::CodeGenUtils::getTerminatorAlias(llvm::Function &func, const llvm::Instruction *instr) {
    auto parentBlock = instr->getParent();
    if(!parentBlock)
    {
        return std::string{};
    }
    auto terminator = parentBlock->getTerminator();
    if(!terminator)
    {
        return std::string{};
    }

    if(auto* branchInstr = llvm::dyn_cast<llvm::BranchInst>(terminator))
    {
        return branchInstr->isConditional() ? branchInstr->getCondition()->getName().str() : std::string{};
    }

    return std::string{};
}

std::string utils::CodeGenUtils::getBranchInstrBodyGivenBlock(llvm::Function &func, const std::string &bbLabel) {
    std::map<std::string, std::string> instructions;
    for(auto& bb : func)
    {
        if(bb.getName() != bbLabel)
        {
           continue;
        }

        for(auto& instr : bb)
        {
           auto myInstr = codeGen::Instruction::getInstruction(instr, 0);
           instructions.insert_or_assign(instr.getName().str(), myInstr->toString());
        }

        auto terminator = bb.getTerminator();
        spdlog::info("Found terminator: {}", bb.getName().str());
        if(auto branchInstr = llvm::dyn_cast<llvm::BranchInst>(terminator))
        {
            if(branchInstr->isConditional())
            {
                spdlog::error("Found Conditional with condition: {}", branchInstr->getCondition()->getName().str());
                auto it = instructions.find(branchInstr->getCondition()->getName().str());
                if(it != instructions.end())
                {
                    spdlog::info("Found branch instr: {}", it->second);
                    return it->second;
                }
            }
        }
    }
    return std::string{};
}

std::string utils::CodeGenUtils::extractLHSFromInstructionBody(const std::string &instrBody) {
    // if I find ' var1 = i > j' I will return i > j
    auto equalPos = instrBody.find(" = ");
    if(equalPos == std::string::npos)
    {
        return instrBody;
    }
    return instrBody.substr(equalPos + 3);
}

utils::CodeGenUtils::BranchToTerminalBlockResult utils::CodeGenUtils::checkIfCurrentBlockBranchesToTerminalBlock(llvm::Function &func, const std::string &bbLabel) {
    auto terminalBlockName = func.back().getName().str();

    auto targetBB  = getBBAfterLabel(func, bbLabel);
    if(!targetBB)
    {
        return BranchToTerminalBlockResult{false, false};
    }

    auto terminator = targetBB->getTerminator();
    if(!terminator)
    {
        return BranchToTerminalBlockResult{false, false};
    }

    if(auto branchInstr = llvm::dyn_cast<llvm::BranchInst>(terminator))
    {
        if(!branchInstr->isConditional()) {
            // unconditional branch probably means is a preheader / loop end
            // just ignore it
            return BranchToTerminalBlockResult{false, false};
        }

        auto leftBranch = branchInstr->getSuccessor(0)->getName().str();
        auto rightBranch = branchInstr->getSuccessor(1)->getName().str();

        if(leftBranch == terminalBlockName || rightBranch == terminalBlockName)
        {
            return leftBranch == terminalBlockName ? BranchToTerminalBlockResult{true, false} : BranchToTerminalBlockResult{true, true};
        }
    }

    return BranchToTerminalBlockResult{false, false};
}

std::string
utils::CodeGenUtils::returnStringForBranchingToTerminalBlock(llvm::Function &func, const std::string &bbLabel) {
    std::string retStr =  "return ";

    codeGen::ast::PHINodeHandler phiNodeHandler{func};
    auto phiAliases = phiNodeHandler.getPHINodeAliases();
    auto foundBBLabel = std::find_if(phiAliases.begin(), phiAliases.end(), [&bbLabel](const auto& stackVar){
        return stackVar.getStackVarName() == bbLabel;
    });

    if(foundBBLabel != phiAliases.end())
    {
        retStr += foundBBLabel->getLocalVar();
    }
    else
    {
        retStr += "0";
    }

    return retStr;
}


