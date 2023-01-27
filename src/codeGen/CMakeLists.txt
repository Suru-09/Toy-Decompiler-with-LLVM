cmake_minimum_required(VERSION 3.22)

add_library(${PROJECT_NAME}-codeGen
)

target_include_directories(${PROJECT_NAME}-codeGen
    PRIVATE
        ${INCL_DIR}
)