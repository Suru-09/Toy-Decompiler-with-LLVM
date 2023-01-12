cmake_minimum_required(VERSION 3.22)

add_library(${PROJECT_NAME}-udm
    cfa/CFG.cpp
    cfa/CFGNode.cpp
)

target_include_directories(${PROJECT_NAME}-udm
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${Capstone_INCLUDE}
        ${INCL_DIR}
)