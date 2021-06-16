#------------------------------------------------------------------------------
# Algebra module.
#------------------------------------------------------------------------------
project(render CXX)

add_library(render
    STATIC
        renderer.cpp
        geometry.cpp
        display_file.cpp
)

target_include_directories(render
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${GTKMM_INCLUDE_DIRS}
)
