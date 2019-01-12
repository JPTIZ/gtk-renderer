cmake_minimum_required(VERSION 3.0)
project(objects CXX)

set(SOURCES
    "beziercurve.cpp"
    "reader.cpp"
    "shapes.cpp"
)

add_library(objects STATIC
    ${SOURCES}
)

target_include_directories(objects
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    PRIVATE
        ${GTKMM_INCLUDE_DIRS}
)
