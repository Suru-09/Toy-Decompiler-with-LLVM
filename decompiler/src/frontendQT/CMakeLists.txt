cmake_minimum_required(VERSION 3.22)

# We need to add QT headers which contain Q_OBJECT macro,
# signals etc. because moc files won't be generated otherwise
set (QT_HEADERS_LIST
    ${CMAKE_SOURCE_DIR}/include/frontendQT/MainWindowQT.h
    ${CMAKE_SOURCE_DIR}/include/frontendQT/MySyntaxHighlighterQT.h
    ${CMAKE_SOURCE_DIR}/include/frontendQT/FileViewerQT.h
    ${CMAKE_SOURCE_DIR}/include/frontendQT/FileSelectorQT.h
)

add_library(${PROJECT_NAME}-frontendQT
    ${QT_HEADERS_LIST}
    MainWindowQT.cpp
    MySyntaxHighlighterQT.cpp
    FileSelectorQT.cpp
    FileViewerQT.cpp
)

target_include_directories(${PROJECT_NAME}-frontendQT
    PRIVATE
        ${INCL_DIR}
)