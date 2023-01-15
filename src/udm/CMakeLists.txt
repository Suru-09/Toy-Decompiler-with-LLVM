cmake_minimum_required(VERSION 3.22)

add_library(${PROJECT_NAME}-udm
    BBInfo.cpp
    FuncInfo.cpp
    FunctionsAnalysis.cpp
    Interval.cpp
    IntervalGraph.cpp
    UDM.cpp
)

target_include_directories(${PROJECT_NAME}-udm
    PRIVATE
        ${INCL_DIR}
)