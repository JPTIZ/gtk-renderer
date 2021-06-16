#------------------------------------------------------------------------------
# Setup project
#------------------------------------------------------------------------------
# Project name and build-system
cmake_minimum_required(VERSION 3.8)
project(gtk-renderer
    VERSION 0.1
    LANGUAGES CXX)

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

#------------------------------------------------------------------------------
# External Libraries
#------------------------------------------------------------------------------
find_library(GTKMM gtkmm-3.0)
find_library(CAIROMM cairomm-1.0)

if(GTKMM_FOUND)
    message(STATUS "GTKMM found!")
    message("       Include  -> \"${GTKMM_INCLUDE_DIRS}\"")
    message("       Libs     -> \"${GTKMM_LIBRARIES}\"")
    message("       Flags    -> \"${GTKMM_CFLAGS_OTHER}\"")
else()
    message(FATAL_ERROR "Failed to find GTKMM. Do you have and GTKMM.cmake?")
endif()

if(CAIROMM_FOUND)
    message(STATUS "CAIROMM found!")
    message("       Include  -> \"${CAIROMM_INCLUDE_DIRS}\"")
    message("       Libs     -> \"${CAIROMM_LIBRARIES}\"")
    message("       Flags    -> \"${CAIROMM_CFLAGS_OTHER}\"")
else()
    message(FATAL_ERROR "Failed to find CAIROMM. Do you have and CAIROMM.cmake?")
endif()

add_definitions(${GTKMM_CFLAGS_OTHER})
add_definitions(${CAIROMM_CFLAGS_OTHER})

#------------------------------------------------------------------------------
# Local sources
#------------------------------------------------------------------------------
# Exportable macro
macro(copy file)
    get_filename_component(base ${file} NAME)
    configure_file(${file} ${PROJECT_BINARY_DIR}/${base} COPYONLY)
endmacro()

add_subdirectory(src/lib)
add_subdirectory(src/app)
