cmake_minimum_required(VERSION 2.8)
project(gui CXX)

set(SOURCES
    "window.cpp"
    #    "dialog.cpp"
)

add_library(gui STATIC
    ${SOURCES}
)

target_include_directories(gui
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    PRIVATE
        ${GTKMM_INCLUDE_DIRS}
)
