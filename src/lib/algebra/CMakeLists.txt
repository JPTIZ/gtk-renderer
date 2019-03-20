#------------------------------------------------------------------------------
# Algebra module.
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8)
project(algebra CXX)

add_library(rudolph
    STATIC
        matrix.cpp
)

target_include_directories(rudolph
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
