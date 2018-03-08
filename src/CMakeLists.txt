cmake_minimum_required(VERSION 3.0)
project(gtk-renderer CXX)

# Add project-specific CMake configs
set(CMAKE_MODULE_PATH
    "${PROJECT_SOURCE_DIR}/cmake"
)

# Set C++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# External libraries

# - GTK+3.0
find_package(GTK3)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

# Project sub-dirs
add_subdirectory(rudolph)

# Final linkings
add_executable(gtk-renderer main.cpp)

target_link_libraries(gtk-renderer ${GTK3_LIBRARIES} rudolph)
