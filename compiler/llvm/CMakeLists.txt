cmake_minimum_required(VERSION 3.18.2)

find_package(LLVM CONFIG REQUIRED)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_library(${PROJECT_NAME}-llvm STATIC
    ASTtoIR.cpp
)

target_include_directories(${PROJECT_NAME}-llvm
    PRIVATE
        ${CMAKE_BINARY_DIR}
)

#llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries(${PROJECT_NAME}-llvm
    PRIVATE
        ${llvm_libs}
)
