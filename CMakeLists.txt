cmake_minimum_required(VERSION 3.22)

# ignore llvm building STATIC instead of SHARED libs
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(CMAKE_CXX_REQUIRED 17)
SET(CMAKE_CXX_STANDARD 17)

SET(arch "arch" CACHE STRING "")

# CAPSTONE DEPENDECIES ----- START --------
if (${arch} STREQUAL "arm64")
    set(Capstone_LIB /Users/suru/Documents/GitCloning/capstone/build)
    set(Capstone_INCLUDE /Users/suru/Documents/GitCloning/capstone/include)
endif()

message(STATUS "Found CAPSTONE ${Capstone_INCLUDE}")
# CAPSTONE DEPENDECIES ----- END --------


# LLVM DEPENDECIES ----- START --------
find_package(LLVM CONFIG REQUIRED)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
# LLVM DEPENDECIES ----- END --------

project(Reverse-Engineering-Tool)

add_subdirectory(src)