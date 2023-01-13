cmake_minimum_required(VERSION 3.22)

add_library(${PROJECT_NAME}-udm
    FncInfo.cpp
    FunctionsAnalysis.cpp
    Interval.cpp
    UDM.cpp
)

target_include_directories(${PROJECT_NAME}-udm
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${Capstone_INCLUDE}
        ${INCL_DIR}
)