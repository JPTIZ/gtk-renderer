#------------------------------------------------------------------------------
# Setup project
#------------------------------------------------------------------------------
# Project name and build-system
cmake_minimum_required(VERSION 2.8)
project(gtk-renderer CXX)

# Add warning flags for g++
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Werror")
endif()

# Show profile and compilation flags
message("Profile: ${CMAKE_BUILD_TYPE}")
message("         Default Flags  ->  ${CMAKE_CXX_FLAGS}")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("         Debug flags    -> ${CMAKE_CXX_FLAGS_DEBUG}")
else()
    message("         Release flags  -> ${CMAKE_CXX_FLAGS_RELEASE}")
endif()

# Set C++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#------------------------------------------------------------------------------
# External Libraries
#------------------------------------------------------------------------------
# - GTKMM
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

if(GTKMM_FOUND)
    message(STATUS "GTKMM found!")
    message("       Include  -> \"${GTKMM_INCLUDE_DIRS}\"")
    message("       Libs     -> \"${GTKMM_LIBRARIES}\"")
    message("       Flags    -> \"${GTKMM_CFLAGS_OTHER}\"")
else()
    message(FATAL_ERROR "Failed to find GTKMM. Do you have and GTKMM.cmake?")
endif()

add_definitions(${GTKMM_CFLAGS_OTHER})

#------------------------------------------------------------------------------
# Local sources
#------------------------------------------------------------------------------
# Exportable macro
macro(copy file)
    get_filename_component(base ${file} NAME)
    configure_file(${file} ${PROJECT_BINARY_DIR}/${base} COPYONLY)
endmacro()

# Set resources dir variable
#set(PROJECT_RESOURCE_DIR "${PROJECT_SOURCE_DIR}/res")

# Local libraries
add_subdirectory(src/rudolph)

# Final executable
add_subdirectory(src/app)
