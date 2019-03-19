#------------------------------------------------------------------------------
# The Rudolph Application itself
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8)
project(app CXX)

set(SOURCES
    "main.cpp"
    "app.cpp"
)

add_executable(app
    ${SOURCES}
)

target_include_directories(app
    PUBLIC
        "../"
        ${CMAKE_CURRENT_LIST_DIR}
    PRIVATE
        ${GTKMM_INCLUDE_DIRS}
)

target_link_libraries(app PUBLIC
    # rudolph
    ${GTKMM_LIBRARIES}
)
