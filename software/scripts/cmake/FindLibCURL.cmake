# Check if we are cross-compiling
if(CMAKE_CROSSCOMPILING)
    message(STATUS "FindLibCURL.cmake: Cross-compiling for aarch64")
    if(DEFINED CMAKE_SYSROOT)
        message(STATUS "FindLibCURL.cmake: Using SYSROOT: ${CMAKE_SYSROOT}")
        set(LibCURL_SEARCH_PATHS
            "${CMAKE_SYSROOT}/usr"
            "${CMAKE_SYSROOT}/usr/local"
            "${CMAKE_SYSROOT}/opt"
        )
    else()
        set(LibCURL_SEARCH_PATHS
            "/usr/aarch64-linux-gnu"
            "/usr/local/aarch64-linux-gnu"
            "/opt/aarch64-linux-gnu"
        )
    endif()
else()
    message(STATUS "FindLibCURL.cmake: Compiling for native architecture")
    set(LibCURL_SEARCH_PATHS
        "/usr"
        "/usr/local"
        "/opt/local"
    )
endif()

# Find the LibCURL library
find_library(LibCURL_LIBRARY
    NAMES libcurl
    PATHS ${SDL2_SEARCH_PATHS}
    PATH_SUFFIXES lib
)

message(STATUS "FindLibCURL.cmake: LibCURL_LIBRARY: ${LibCURL_LIBRARY}")

# Find the LibCURL include directory
find_path(LibCURL_INCLUDE_DIR
    NAMES curl.h
    PATHS ${LibCURL_SEARCH_PATHS}
    PATH_SUFFIXES include/curl
)

message(STATUS "FindLibCURL.cmake: LibCURL_INCLUDE_DIR: ${LibCURL_INCLUDE_DIR}")

# Check if the library and include directory were found
if(SDL2_LIBRARY AND SDL2_INCLUDE_DIR)
    set(SDL2_FOUND TRUE)
    set(SDL2_LIBRARIES ${SDL2_LIBRARY})
    set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR})

    add_library(SDL2::SDL2 UNKNOWN IMPORTED)
    set_target_properties(LibCURL::LibCURL PROPERTIES
        IMPORTED_LOCATION ${LibCURL_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${SDL2_INCLUDE_DIR}
    )
else()
    message(STATUS "Could not find LibCURL lib and include directory")
    set(LibCURL_FOUND FALSE)
endif()

# Provide the results to the parent scope
mark_as_advanced(LibCURL_LIBRARY LibCURL_INCLUDE_DIR)
