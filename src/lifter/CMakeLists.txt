cmake_minimum_required(VERSION 3.22)

add_library(${PROJECT_NAME}-lifter
    ARM64Strategy.cpp
    ELFVisitor.cpp
    ExecutableType.cpp
    LifterContext.cpp
    StrategyFactory.cpp
    VisitorFactory.cpp
    X86Strategy.cpp
)

target_include_directories(${PROJECT_NAME}-lifter
    PRIVATE
        ${CMAKE_BINARY_DIR}
        ${CMAKE_SOURCE_DIR}/include
        ${Capstone_INCLUDE}
        ${LLVM_INCLUDE_DIRS}
)