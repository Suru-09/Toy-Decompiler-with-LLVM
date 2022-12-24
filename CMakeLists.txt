cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_REQUIRED 17)
SET(CMAKE_CXX_STANDARD 17)


# LLVM DEPENDECIES ----- START --------
#find_package(LLVM CONFIG REQUIRED)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
# LLVM DEPENDECIES ----- END --------


project(Reverse-Engineering-Tool)

add_executable(${PROJECT_NAME}  
    main.cpp
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        ${llvm_libs}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_BINARY_DIR}
)