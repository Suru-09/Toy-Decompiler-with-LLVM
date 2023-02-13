cmake_minimum_required(VERSION 3.22)

project(Reverse-Engineering-Tool)

# ignore llvm building STATIC instead of SHARED libs
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(CMAKE_CXX_REQUIRED 17)
SET(CMAKE_CXX_STANDARD 17)

SET(arch "arch" CACHE STRING "")
SET(work "work" CACHE STRING "")

message(STATUS "Architecture compiled on: <${arch}>")

find_package(capstone REQUIRED)

# # CAPSTONE DEPENDECIES ----- START --------
if (${arch} STREQUAL "arm64")
    set(Capstone_LIB /Users/suru/Documents/GitCloning/capstone/build)
    set(Capstone_INCLUDE /Users/suru/Documents/GitCloning/capstone/include)
elseif(${arch} STREQUAL "x86")
    if(${work} STREQUAL "ON")
        #set(Capstone_LIB /home/users/dragoss/Documents/licenta/capstone/build)
        #set(Capstone_INCLUDE /home/users/dragoss/Documents/licenta/capstone/include)
        set(Capstone_LIB /home/suru/Documents/GitCloning/capstone/build)
        set(Capstone_INCLUDE /home/suru/Documents/GitCloning/capstone/include)
    elseif(${work} STREQUAL "OFF")
        set(Capstone_LIB /mnt/d/GithubCloning/capstone/build)
        set(Capstone_INCLUDE /mnt/d/GithubCloning/capstone/include)
    endif()
endif()

message(STATUS "Found CAPSTONE: <${Capstone_INCLUDE}>")
# # CAPSTONE DEPENDECIES ----- END --------

# LLVM DEPENDECIES ----- START --------
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM: <${LLVM_PACKAGE_VERSION}>")
message(STATUS "Using LLVMConfig.cmake in: <${LLVM_DIR}>")

include_directories(${LLVM_INCLUDE_DIRS})
#separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

# LLVM DEPENDECIES ----- END --------


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

set(CXX_FLAGS 
    -O3
)

add_subdirectory(src)
#add_subdirectory(test)