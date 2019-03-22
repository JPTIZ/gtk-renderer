cmake_minimum_required(VERSION 3.0)
project(utils CXX)

set(SOURCES
    "command.cpp"
    "geometry.cpp"
)

add_library(utils STATIC
    ${SOURCES}
)

target_include_directories(utils
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    PRIVATE
        ${GTKMM_INCLUDE_DIRS}
)
