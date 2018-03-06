cmake_minimum_required(VERSION 3.0)
project(app CXX)
set(SOURCE
    window.cpp
)

UTILS_LIBRARY(app ${SOURCE})

target_link_libraries(app
    engine
    ${SFML_LIBRARIES}
    ${OPENGL_LIBRARIES}
)
target_include_directories(app PUBLIC
    ${engine_SOURCE_DIR}
    ${SFML_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
)
