cmake_minimum_required(VERSION 3.22)

add_library(${PROJECT_NAME}-codeGen
    CodeGeneration.cpp
    LoopGen.cpp
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
)

target_include_directories(${PROJECT_NAME}-codeGen
    PRIVATE
        ${INCL_DIR}
)