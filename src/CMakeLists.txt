cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_REQUIRED 17)
SET(CMAKE_CXX_STANDARD 17)

set(CXX_FLAGS 
    -O3
)

add_subdirectory(udm)
add_subdirectory(utils)
add_subdirectory(lifter)


add_executable(${PROJECT_NAME}  
    main.cpp
)

# Selecting which libraries of LLVM are being used
# and then append them to the llvm_libs variable
# so that they can be later linked to the executable
llvm_map_components_to_libnames(llvm_libs support core irreader object analysis)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        ${PROJECT_NAME}-udm
        ${PROJECT_NAME}-utils
        ${PROJECT_NAME}-lifter
        ${Capstone_LIB}/libcapstone.a
        # DO NOT MOVE LLVM UPPER(it will try to link it wrongly 
        # -> linking errors in .txt sections of own libs)
        ${llvm_libs}
        spdlog::spdlog
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${INCL_DIR}
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        ${CXX_FLAGS}
)