cmake_minimum_required(VERSION 3.22.1)

include(FindRE2C.cmake)

find_package(BISON 3.8.2)
find_package(RE2C)

if (BISON_FOUND AND RE2C_EXECUTABLE)

    set(BISON_OUTPUT ${CMAKE_BINARY_DIR}/bison/toy_parser.cc)
    BISON_TARGET(parser toy_parser.yy toy_parser.cc DEFINES_FILE ${CMAKE_BINARY_DIR}/bison/toy_parser.hh)

    RE2C_TARGET(NAME lexer
         INPUT ${BISON_parser_OUTPUTS}
         OUTPUT ${CMAKE_BINARY_DIR}/bison/toy_parser.cpp )
endif()

add_library(bizonu
    ${CMAKE_BINARY_DIR}/bison/toy_parser.cpp
    ${BISON_parser_OUTPUTS}
    
)

set_target_properties(bizonu PROPERTIES LINKER_LANGUAGE CXX)


