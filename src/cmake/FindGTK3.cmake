if(GTK3_FOUND)
    return()
endif()

find_package(PkgConfig)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

add_library(gtk3 INTERFACE IMPORTED)

set_property(TARGET gtk3
    PROPERTY INTERFACE_INCLUDE_DIRECTORIES
    "${GTK3_INCLUDE_DIRS}"
)

set_property(TARGET gtk3
    PROPERTY INTERFACE_LINK_LIBRARIES
    "${GTK3_LIBRARIES}"
)

set_property(TARGET gtk3
    PROPERTY INTERFACE_COMPILE_OPTIONS
    "${GTK3_CFLAGS_OTHER}"
)
