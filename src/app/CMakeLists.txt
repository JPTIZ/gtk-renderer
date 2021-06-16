#------------------------------------------------------------------------------
# The Rudolph Application itself
#------------------------------------------------------------------------------
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

target_link_libraries(app
    PUBLIC
        rudolph
        ${GTKMM_LIBRARIES}
)

# Set C++20 standard
target_compile_features(app PUBLIC cxx_std_20)
set_target_properties(app PROPERTIES CXX_EXTENSIONS OFF)
