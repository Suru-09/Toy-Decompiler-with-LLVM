cmake_minimum_required(VERSION 3.22)

add_library(${PROJECT_NAME}-logger
    LoggerManager.cpp
)

target_include_directories(${PROJECT_NAME}-logger
    PRIVATE
        ${INCL_DIR}
)