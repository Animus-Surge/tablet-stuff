# Check if we are cross-compiling
if(CMAKE_CROSSCOMPILING)
    message(STATUS "FindSDL2_ttf.cmake: Cross-compiling for aarch64")
    if(DEFINED CMAKE_SYSROOT)
        message(STATUS "FindSDL2_ttf.cmake: Using SYSROOT: ${CMAKE_SYSROOT}")
        set(SDL2_TTF_SEARCH_PATHS
            "${CMAKE_SYSROOT}/usr"
            "${CMAKE_SYSROOT}/usr/local"
            "${CMAKE_SYSROOT}/opt"
        )
    else()
        set(SDL2_TTF_SEARCH_PATHS
            "/usr/aarch64-linux-gnu"
            "/usr/local/aarch64-linux-gnu"
            "/opt/aarch64-linux-gnu"
        )
    endif()
else()
    message(STATUS "FindSDL2_ttf.cmake: Compiling for native architecture")
    set(SDL2_TTF_SEARCH_PATHS
        "/usr"
        "/usr/local"
        "/opt/local"
    )
endif()

# Find the SDL2 library
find_library(SDL2_TTF_LIBRARY
    NAMES SDL2_ttf
    PATHS ${SDL2_TTF_SEARCH_PATHS}
    PATH_SUFFIXES lib
)

message(STATUS "FindSDL2_ttf.cmake: SDL2_TTF_LIBRARY: ${SDL2_TTF_LIBRARY}")

# Find the SDL2 include directory
find_path(SDL2_TTF_INCLUDE_DIR
    NAMES SDL_ttf.h
    PATHS ${SDL2_TTF_SEARCH_PATHS}
    PATH_SUFFIXES include/SDL2
)

message(STATUS "FindSDL2_ttf.cmake: SDL2_TTF_INCLUDE_DIR: ${SDL2_TTF_INCLUDE_DIR}")

# Check if the library and include directory were found
if(SDL2_LIBRARY AND SDL2_TTF_INCLUDE_DIR)
    set(SDL2_TTF_FOUND TRUE)
    set(SDL2_TTF_LIBRARIES ${SDL2_TTF_LIBRARY})
    set(SDL2_TTF_INCLUDE_DIRS ${SDL2_TTF_INCLUDE_DIR})

    add_library(SDL2::SDL2_ttf UNKNOWN IMPORTED)
    set_target_properties(SDL2::SDL2_ttf PROPERTIES
        IMPORTED_LOCATION ${SDL2_TTF_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${SDL2_TTF_INCLUDE_DIR}
    )
else()
    set(SDL2_TTF_FOUND FALSE)
endif()

# Provide the results to the parent scope
mark_as_advanced(SDL2_TTF_LIBRARIES SDL2_TTF_INCLUDE_DIR)
