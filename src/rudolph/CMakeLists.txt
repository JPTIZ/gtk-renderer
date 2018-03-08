cmake_minimum_required(VERSION 3.0)
project(rudolph CXX)

set(SOURCES
    window.cpp
    rudolph.cpp
    render.cpp
    "objects/shapes.cpp"
)

add_library(rudolph STATIC
    ${SOURCES}
)

target_include_directories(rudolph
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
