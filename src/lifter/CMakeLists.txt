cmake_minimum_required(VERSION 3.22)

add_library(${PROJECT_NAME}-lifter
    ARM64Strategy.cpp
    ExecutableType.cpp
    LifterContext.cpp
    StrategyFactory.cpp
    X86_64ELFStrategy.cpp
    X86_64StrategyFactory.cpp
    ARM64StrategyFactory.cpp
)

target_include_directories(${PROJECT_NAME}-lifter
    PRIVATE
        ${CMAKE_BINARY_DIR}
        ${CMAKE_SOURCE_DIR}/include
        ${Capstone_INCLUDE}
        ${LLVM_INCLUDE_DIRS}
)