cmake_minimum_required(VERSION 3.18.3)

add_library(${PROJECT_NAME}-graphviz STATIC 
    AstViz.cpp
)

target_include_directories(${PROJECT_NAME}-graphviz 
    PUBLIC
        ${CMAKE_BINARY_DIR}
)