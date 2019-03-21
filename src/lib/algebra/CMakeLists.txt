#------------------------------------------------------------------------------
# Algebra module.
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8)
project(algebra CXX)

add_library(algebra
    STATIC
        matrix.cpp
)

target_include_directories(algebra
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
