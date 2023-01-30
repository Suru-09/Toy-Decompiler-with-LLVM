cmake_minimum_required(VERSION 3.22)

add_library(${PROJECT_NAME}-codeGen
    CodeGeneration.cpp
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