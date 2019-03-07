#------------------------------------------------------------------------------
# Rudolph's library modules.
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.0)
project(rudolph CXX)

set(SOURCES
    "rudolph.cpp"
)

add_subdirectory(gui)

add_library(rudolph STATIC
    ${SOURCES}
)

target_link_libraries(rudolph
    PUBLIC
        gui
    PRIVATE
        ${GTKMM_LIBRARIES}
)

target_include_directories(rudolph
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    PRIVATE
        ${GTKMM_INCLUDE_DIRS}
)

copy("${PROJECT_SOURCE_DIR}/gui/mainwindow.ui")
copy("${PROJECT_SOURCE_DIR}/gui/newobject.ui")
