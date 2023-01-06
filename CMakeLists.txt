cmake_minimum_required(VERSION 3.22)


project(Reverse-Engineering-Tool)

# ignore llvm building STATIC instead of SHARED libs
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(CMAKE_CXX_REQUIRED 17)
SET(CMAKE_CXX_STANDARD 17)

SET(arch "arch" CACHE STRING "")

# CAPSTONE DEPENDECIES ----- START --------
if (${arch} STREQUAL "arm64")
    set(Capstone_LIB /Users/suru/Documents/GitCloning/capstone/build)
    set(Capstone_INCLUDE /Users/suru/Documents/GitCloning/capstone/include)
elseif(${arch} STREQUAL "x86")
    set(Capstone_LIB /mnt/d/GithubCloning/capstone/build)
    set(Capstone_INCLUDE /mnt/d/GithubCloning/capstone/include)
endif()

message(STATUS "Found CAPSTONE ${Capstone_INCLUDE}")
# CAPSTONE DEPENDECIES ----- END --------

# set (ZLIB_LIBRARY "/opt/homebrew/Cellar/zlib/1.2.13/")
# set (ZLIB_INCLUDE_DIR "/opt/homebrew/Cellar/zlib/1.2.13/include")

# LLVM DEPENDECIES ----- START --------
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

# LLVM DEPENDECIES ----- END --------


# SPDLOG DEPENDECIES ----- START --------
find_package(spdlog REQUIRED)

message(STATUS "Found SPDLOG ${spdlog_INCLUDE_DIRS}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

# LLSPDLOGVM DEPENDECIES ----- END --------

add_subdirectory(src)