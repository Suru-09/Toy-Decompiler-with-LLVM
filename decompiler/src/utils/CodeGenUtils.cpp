#include <llvm/IR/Instructions.h>
#include <regex>
#include "utils/CodeGenUtils.h"


#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"


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
    spdlog::error("Extracted end and start: {}, {}", endPos, startPos);
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

std::string utils::CodeGenUtils::getLoopCondition(llvm::Function &func, const std::string &bbLabel) {
    for(auto& bb : func)
    {
        if(bb.getName() == bbLabel)
        {
           auto terminator = bb.getTerminator();
              if(terminator->getNumSuccessors() == 2)
              {
                auto cond = llvm::dyn_cast<llvm::BranchInst>(terminator)->getCondition();
                return cond->getName().str();
              }
        }
    }
    return std::string{};
}


