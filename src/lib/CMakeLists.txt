#------------------------------------------------------------------------------
# Rudolph's library modules.
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8)
project(rudolph CXX)

add_subdirectory(algebra)
add_subdirectory(render)

add_library(rudolph
    STATIC
        algebra
        render
)

target_link_libraries(rudolph
    PUBLIC
        algebra
        render
    PRIVATE
        ${GTKMM_LIBRARIES}
)

target_include_directories(rudolph
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    PRIVATE
        ${GTKMM_INCLUDE_DIRS}
)
