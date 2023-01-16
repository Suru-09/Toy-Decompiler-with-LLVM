cmake_minimum_required(VERSION 3.22)

add_library(${PROJECT_NAME}-utils
    LifterUtils.cpp
    UdmUtils.cpp
)

target_include_directories(${PROJECT_NAME}-utils
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${Capstone_INCLUDE}
        ${INCL_DIR}
)