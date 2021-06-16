#------------------------------------------------------------------------------
# Render module.
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

# Set C++20 standard
target_compile_features(render PUBLIC cxx_std_20)
set_target_properties(render PROPERTIES CXX_EXTENSIONS OFF)
