# Check if we are cross-compiling
if(CMAKE_CROSSCOMPILING)
    message(STATUS "FindSDL2.cmake: Cross-compiling for aarch64")
    if(DEFINED CMAKE_SYSROOT)
        message(STATUS "FindSDL2.cmake: Using SYSROOT: ${CMAKE_SYSROOT}")
        set(SDL2_SEARCH_PATHS
            "${CMAKE_SYSROOT}/usr"
            "${CMAKE_SYSROOT}/usr/local"
            "${CMAKE_SYSROOT}/opt"
        )
    else()
        set(SDL2_SEARCH_PATHS
            "/usr/aarch64-linux-gnu"
            "/usr/local/aarch64-linux-gnu"
            "/opt/aarch64-linux-gnu"
        )
    endif()
else()
    message(STATUS "FindSDL2.cmake: Compiling for native architecture")
    set(SDL2_SEARCH_PATHS
        "/usr"
        "/usr/local"
        "/opt/local"
    )
endif()

# Find the SDL2 library
find_library(SDL2_LIBRARY
    NAMES SDL2
    PATHS ${SDL2_SEARCH_PATHS}
    PATH_SUFFIXES lib
)

message(STATUS "FindSDL2.cmake: SDL2_LIBRARY: ${SDL2_LIBRARY}")

# Find the SDL2 include directory
find_path(SDL2_INCLUDE_DIR
    NAMES SDL.h
    PATHS ${SDL2_SEARCH_PATHS}
    PATH_SUFFIXES include/SDL2
)

message(STATUS "FindSDL2.cmake: SDL2_INCLUDE_DIR: ${SDL2_INCLUDE_DIR}")

# Check if the library and include directory were found
if(SDL2_LIBRARY AND SDL2_INCLUDE_DIR)
    set(SDL2_FOUND TRUE)
    set(SDL2_LIBRARIES ${SDL2_LIBRARY})
    set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR})

    add_library(SDL2::SDL2 UNKNOWN IMPORTED)
    set_target_properties(SDL2::SDL2 PROPERTIES
        IMPORTED_LOCATION ${SDL2_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${SDL2_INCLUDE_DIR}
    )
else()
    message(STATUS "Could not find SDL2 lib and include directory")
    set(SDL2_FOUND FALSE)
endif()

# Provide the results to the parent scope
mark_as_advanced(SDL2_LIBRARY SDL2_INCLUDE_DIR)
