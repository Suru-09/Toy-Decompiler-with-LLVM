cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_REQUIRED 17)
SET(CMAKE_CXX_STANDARD 17)

add_subdirectory(lifter)


add_executable(${PROJECT_NAME}  
    main.cpp
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        ${llvm_libs}
        ${Capstone_LIB}/libcapstone.a
        ${PROJECT_NAME}-lifter
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_BINARY_DIR}
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/test
        ${Capstone_INCLUDE}/
)