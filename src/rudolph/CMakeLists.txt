cmake_minimum_required(VERSION 3.0)
project(rudolph CXX)

set(SOURCES
    "rudolph.cpp"
)

add_subdirectory(gui)
# add_subdirectory(render)
# add_subdirectory(objects)
# add_subdirectory(utils)

add_library(rudolph STATIC
    ${SOURCES}
)

target_link_libraries(rudolph PUBLIC
    gui
    #    render
    #    objects
    #    utils
    ${GTKMM_LIBRARIES}
)

target_include_directories(rudolph
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    PRIVATE
        ${GTKMM_INCLUDE_DIRS}
)
