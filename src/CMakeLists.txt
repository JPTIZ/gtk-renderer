cmake_minimum_required(VERSION 3.0)

project(gtk-renderer CXX)

set(CMAKE_MODULE_PATH
    "${PROJECT_SOURCE_DIR}/cmake"
)

find_package(GTK3)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(gtk-renderer main.cpp)

target_link_libraries(gtk-renderer ${GTK3_LIBRARIES})
