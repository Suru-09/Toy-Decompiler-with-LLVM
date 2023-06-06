cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)


set(TEST_SOURCES
    udm/UdmTest.cpp
    udm/IntervalTest.cpp
    udm/IntervalGraphTest.cpp
)

add_executable(${PROJECT_NAME}-test
        ${TEST_SOURCES}
        main.cpp
)

# Selecting which libraries of LLVM are being used
# and then append them to the llvm_libs variable
# so that they can be later linked to the executable
llvm_map_components_to_libnames(llvm_libs support core irreader object analysis)

# linking the google library
target_link_libraries(${PROJECT_NAME}-test
    PRIVATE
        ${PROJECT_NAME}-frontendQT
        ${PROJECT_NAME}-udm
        ${PROJECT_NAME}-logger
        ${PROJECT_NAME}-utils
        ${PROJECT_NAME}-lifter
        ${PROJECT_NAME}-codeGen
        ${PROJECT_NAME}-settings
        # DO NOT MOVE LLVM UPPER(it will try to link it wrongly 
        # -> linking errors in .txt sections of own libs)
        ${llvm_libs}
        spdlog::spdlog
        cpprestsdk::cpprest
        OpenSSL::SSL
        CURL::libcurl 
        gtest
        gtest_main
        Qt6::Core Qt6::Gui Qt6::Widgets
)

target_include_directories(${PROJECT_NAME}-test
    PRIVATE
        ${gtest_SOURCE_DIR}/include 
        ${gtest_SOURCE_DIR}
        ${INCL_DIR}
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        ${CXX_FLAGS}
)