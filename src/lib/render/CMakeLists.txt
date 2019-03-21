#------------------------------------------------------------------------------
# Algebra module.
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8)
project(render CXX)

add_library(rudolph
    STATIC
        window.cpp
)

target_include_directories(rudolph
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)