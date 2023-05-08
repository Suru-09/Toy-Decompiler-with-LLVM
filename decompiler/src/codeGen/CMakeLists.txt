cmake_minimum_required(VERSION 3.22)

add_library(${PROJECT_NAME}-codeGen
    CodeGeneration.cpp
    LoopHandler.cpp
    BranchConditionalGen.cpp
    GenerateFnBody.cpp
    GenerateFnHeader.cpp
    ExpandedInstr.cpp
    RenameVariables.cpp
    TranslateOperator.cpp
    InstructionExpander.cpp
    InstructionInfo.cpp
    InstructionInfoRepo.cpp
    instructions/Instruction.cpp
    instructions/BinaryInstruction.cpp
    instructions/TerminatorInstruction.cpp
    instructions/UnaryInstruction.cpp
    instructions/OtherInstruction.cpp
    instructions/BitwiseBinaryInstruction.cpp
    instructions/ConversionInstruction.cpp
    ast/HllAstNode.cpp
    ast/LlvmInstructionNode.cpp
    ast/LlvmFunctionNode.cpp
    ast/LlvmBasicBlockNode.cpp
    ast/GenerateFileVisitor.cpp
    BracketManager.cpp
    DefineVariablesHandler.cpp
        Variable.cpp)

target_include_directories(${PROJECT_NAME}-codeGen
    PRIVATE
        ${INCL_DIR}
)