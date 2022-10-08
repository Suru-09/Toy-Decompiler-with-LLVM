cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_REQUIRED 17)
SET(CMAKE_CXX_STANDARD 17)

project(Bison-Parser VERSION 0.0 LANGUAGES C CXX)

add_subdirectory(bison)
add_subdirectory(graphviz)
add_subdirectory(llvm)


add_executable(${PROJECT_NAME}  
    main.cpp
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        bizonu          
        ${PROJECT_NAME}-graphviz
        ${PROJECT_NAME}-llvm
)

add_dependencies(${PROJECT_NAME}-graphviz bizonu)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_BINARY_DIR}
)
