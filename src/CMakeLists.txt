cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_REQUIRED 17)
SET(CMAKE_CXX_STANDARD 17)

set(CXX_FLAGS 
    -o3
)


add_subdirectory(lifter)


add_executable(${PROJECT_NAME}  
    main.cpp
)

# Selecting which libraries of LLVM are being used
# and then append them to the llvm_libs variable
# so that they can be later linked to the executable
llvm_map_components_to_libnames(llvm_libs support core irreader object)

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
        ${Capstone_INCLUDE}
        ${LLVM_INCLUDE_DIRS}
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        ${CXX_FLAGS}
)