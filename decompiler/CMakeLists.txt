cmake_minimum_required(VERSION 3.22)

project(Reverse-Engineering-Tool)

# ignore building STATIC instead of SHARED libs
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(CMAKE_CXX_REQUIRED 17)
SET(CMAKE_CXX_STANDARD 17)

SET(arch "arch" CACHE STRING "")

message(STATUS "Architecture compiled on: <${arch}>")

# LLVM DEPENDECIES ----- START --------
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM: <${LLVM_PACKAGE_VERSION}>")
message(STATUS "Using LLVMConfig.cmake in: <${LLVM_DIR}>")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS_LIST})
# LLVM DEPENDECIES ----- END --------

# CPPREST DEPENDECIES ----- START --------

find_package(cpprestsdk REQUIRED)

include_directories(${cpprestsdk_INCLUDE_DIRS})

if(cpprestsdk_FOUND)
    message(STATUS "=====================================")
    message(STATUS "cpprestsdk_DIR          : ${cpprestsdk_DIR}")
    message(STATUS "cpprestsdk_VERSION      : ${cpprestsdk_VERSION}")
    message(STATUS "cpprestsdk_INCLUDE_DIRS : ${cpprestsdk_INCLUDE_DIRS}")
    message(STATUS "cpprestsdk_INCLUDE_DIR  : ${cpprestsdk_INCLUDE_DIR}")
    message(STATUS "cpprestsdk_LIBRARIES    : ${cpprestsdk_LIBS}")
    message(STATUS "=====================================")
    message(STATUS "OPENSSL_VERSION      : ${OPENSSL_VERSION}")
    message(STATUS "OPENSSL_INCLUDE_DIR  : ${OPENSSL_INCLUDE_DIR}")
    message(STATUS "OPENSSL_LIBRARIES    : ${OPENSSL_LIBRARIES}")
    message(STATUS "=====================================")
endif(cpprestsdk_FOUND)

# CPPREST DEPENDECIES ----- END --------

# SPDLOG DEPENDECIES ----- START --------
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

if(${arch} STREQUAL "arm64")
    set(spdlog_INCLUDE_DIRS /opt/homebrew/Cellar/spdlog/1.11.0/include)
    set(fmt_INCLUDE_DIRS /opt/homebrew/Cellar/fmt/9.1.0/include)
endif()    

message(STATUS "Found SPDLOG in: <${spdlog_INCLUDE_DIRS}>")
# SPDLOG DEPENDECIES ----- END --------

# GOOGLE TEST DEPENDECIES ----- START --------

find_package(GTest REQUIRED)
message(STATUS "Found GTEST in: <${gtest_SOURCE_DIR}>")

# GOOGLE TEST DEPENDECIES ----- END --------

# Include dirs for C++ files
set(INCL_DIR
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/test
    ${CMAKE_SOURCE_DIR}/testing_files
    ${Capstone_INCLUDE}
    ${LLVM_INCLUDE_DIRS}
    ${spdlog_INCLUDE_DIRS}
    $<$<STREQUAL:"${arch}","arm64">:${fmt_INCLUDE_DIRS}>
)

# compiling flags
set(CXX_FLAGS 
    -O3
)

add_subdirectory(src)
#add_subdirectory(test)