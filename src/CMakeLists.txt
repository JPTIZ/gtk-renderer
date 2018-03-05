cmake_minimum_required(VERSION 3.0)

project(gtk-renderer CXX)

set(CMAKE_MODULE_PATH
    "${PROJECT_SOURCE_DIR}/cmake"
)

find_package(GTK3)

add_executable(gtk-renderer
    main.cpp
)

target_link_libraries(gtk-renderer
    gtk3
)
