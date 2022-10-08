cmake_minimum_required(VERSION 3.22.1)

# FindRE2C.cmake required, because they do not have some kind of package provided to CMake
# Therefore we should be sure that RE2C is installed on the machine running
include(FindRE2C.cmake)

find_package(BISON 3.8.2)

message(STATUS "Found bison: ${BISON_VERSION}")
message(STATUS "Using bison.cmake in: ${BISON_EXECUTABLE}")

message(STATUS "Found RE2C ${RE2C_VERSION}")
message(STATUS "Using RE2C.cmake in: ${RE2C_EXECUTABLE}")

if (BISON_FOUND AND RE2C_EXECUTABLE)

    set(BISON_OUTPUT ${CMAKE_BINARY_DIR}/bison/toy_parser.cc)
    BISON_TARGET(parser toy_parser.yy toy_parser.cc DEFINES_FILE ${CMAKE_BINARY_DIR}/bison/toy_parser.hh)

    RE2C_TARGET(NAME lexer
         INPUT ${BISON_parser_OUTPUTS}
         OUTPUT ${CMAKE_BINARY_DIR}/bison/toy_parser.cpp )
endif()

add_library(bizonu STATIC
    ${CMAKE_BINARY_DIR}/bison/toy_parser.cpp
    ${BISON_parser_OUTPUTS}
)

set_target_properties(bizonu PROPERTIES LINKER_LANGUAGE CXX)


