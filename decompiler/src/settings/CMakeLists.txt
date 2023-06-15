cmake_minimum_required(VERSION 3.22)

add_library(${PROJECT_NAME}-settings
    CodegenSettings.cpp
    LifterSettings.cpp
    UdmSettings.cpp
        ../../include/settings/FileManager.h ../../include/settings/JSONFileManager.h JSONFileManager.cpp)

target_include_directories(${PROJECT_NAME}-settings
    PRIVATE
        ${INCL_DIR}
)