cmake_minimum_required(VERSION 3.0)
project(render CXX)

set(SOURCES
    "camerawindow.cpp"
    "clipper.cpp"
    "render.cpp"
)

add_library(render STATIC
    ${SOURCES}
)

target_include_directories(render
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    PRIVATE
        ${GTKMM_INCLUDE_DIRS}
)
