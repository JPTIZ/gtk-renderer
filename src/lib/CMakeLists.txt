#------------------------------------------------------------------------------
# Rudolph's library modules.
#------------------------------------------------------------------------------
project(rudolph CXX)

#add_subdirectory(lin_algebra)
add_subdirectory(render)

add_library(rudolph
    STATIC
        # algebra
        render
)

target_link_libraries(rudolph
    PUBLIC
        # algebra
        render
    PRIVATE
        ${GTKMM_LIBRARIES}
        ${CAIROMM_LIBRARIES}
)

target_include_directories(rudolph
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    PRIVATE
        ${GTKMM_INCLUDE_DIRS}
        ${CAIROMM_INCLUDE_DIRS}
)

# Set C++20 standard
target_compile_features(rudolph PUBLIC cxx_std_20)
set_target_properties(rudolph PROPERTIES CXX_EXTENSIONS OFF)
