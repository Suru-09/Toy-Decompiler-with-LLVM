cmake_minimum_required(VERSION 3.22)

add_library(${PROJECT_NAME}-lifter
    LifterContext.cpp
    ARM64Strategy.cpp
    X86Strategy.cpp
)

target_include_directories(${PROJECT_NAME}-lifter
    PRIVATE
        ${CMAKE_BINARY_DIR}
        ${CMAKE_SOURCE_DIR}/include
        ${Capstone_INCLUDE}
        ${LLVM_INCLUDE_DIRS}
)