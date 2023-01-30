#include "utils/CodeGenUtils.h"


std::string utils::CodeGenUtils::generateSpaces(int numSpaces)
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

std::string utils::CodeGenUtils::typeToString(llvm::Type::TypeID typeID)
{
    switch(typeID)
    {
        case llvm::Type::TypeID::HalfTyID:
            return "HalfTyID";
        case llvm::Type::TypeID::BFloatTyID:
            return "BFloatTyID";
        case llvm::Type::TypeID::FloatTyID:
            return "FloatTyID";
        case llvm::Type::TypeID::DoubleTyID:
            return "DoubleTyID";
        case llvm::Type::TypeID::X86_FP80TyID:
            return "X86_FP80TyID";
        case llvm::Type::TypeID::FP128TyID:
            return "FP128TyID";
        case llvm::Type::TypeID::PPC_FP128TyID:
            return "PPC_FP128TyID";
        case llvm::Type::TypeID::VoidTyID:
            return "VoidTyID";
        case llvm::Type::TypeID::LabelTyID:
            return "LabelTyID";
        case llvm::Type::TypeID::MetadataTyID:
            return "MetadataTyID";
        case llvm::Type::TypeID::X86_MMXTyID:
            return "X86_MMXTyID";
        case llvm::Type::TypeID::X86_AMXTyID:
            return "X86_AMXTyID";
        case llvm::Type::TypeID::TokenTyID:
            return "TokenTyID";
        case llvm::Type::TypeID::IntegerTyID:
            return "IntegerTyID";
        case llvm::Type::TypeID::PointerTyID:
            return "PointerTyID";
        default:
            return "Unknown Type";
    }

    return "NULL";
}