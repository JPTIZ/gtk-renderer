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

add_definitions(${GTK3_CFLAGS_OTHER})

# Project sub-dirs
add_subdirectory(rudolph)

macro(copy file)
    get_filename_component(base ${file} NAME)
    configure_file(${file} ${PROJECT_BINARY_DIR}/${base} COPYONLY)
endmacro()

copy("${PROJECT_SOURCE_DIR}/rudolph/gui/mainwindow.ui")
copy("${PROJECT_SOURCE_DIR}/rudolph/gui/newobject.ui")

# Final linkings
add_executable(gtk-renderer main.cpp)
target_include_directories(gtk-renderer PRIVATE ${GTK3_INCLUDE_DIRS})

target_link_libraries(gtk-renderer rudolph ${GTK3_LIBRARIES})
