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

set (ZLIB_LIBRARY "/opt/homebrew/Cellar/zlib/1.2.13/")
set (ZLIB_INCLUDE_DIR "/opt/homebrew/Cellar/zlib/1.2.13/include")

# LLVM DEPENDECIES ----- START --------
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

#llvm_map_components_to_libnames(llvm_libs support core irreader)
# LLVM DEPENDECIES ----- END --------

project(Reverse-Engineering-Tool)

add_subdirectory(src)