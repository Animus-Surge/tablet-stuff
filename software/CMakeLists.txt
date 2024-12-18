cmake_minimum_required(VERSION 3.10)

# Make clangd work with cmake
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/scripts/cmake/")

include(ExternalProject)

# Project setup
project(pda_tablet VERSION 1.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Get sources
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# Symlink resources directory to output directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND rm -rf $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

# Build mode checks
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE PDA_DEBUG)
endif()


# External libraries (Submodules, grabbed using ExternalProject)

#Nlohmann JSON
if(EXISTS ${CMAKE_BINARY_DIR}/external/include/nlohmann/json.hpp)
    message(STATUS "Nlohmann JSON already exists, skipping...")
else()
    message(STATUS "Nlohmann JSON does not exist, building...")
    ExternalProject_Add(
        nlohmann_json
        PREFIX ${CMAKE_BINARY_DIR}/external
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_PROGRESS 1
        GIT_TAG v3.11.3
        BUILD_ALWAYS OFF
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/external
    )

    add_dependencies(${PROJECT_NAME} nlohmann_json)
endif()

# LuaJIT
ExternalProject_Add(
    luajit
    PREFIX ${CMAKE_BINARY_DIR}/external
    GIT_REPOSITORY "https://github.com/LuaJIT/LuaJIT.git"
    GIT_TAG "v2.1"
    UPDATE_COMMAND ""
    BUILD_IN_SOURCE ON
    CONFIGURE_COMMAND ""
    BUILD_COMMAND make
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(luajit BINARY_DIR SOURCE_DIR)

set(LUAJIT_LIBRARIES ${BINARY_DIR}/src/libluajit.a)
set(LUAJIT_INCLUDE_DIRS ${SOURCE_DIR}/src)

add_dependencies(${PROJECT_NAME} luajit)

set(NLOHMANN_JSON_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/external/include)

# Distro package manager libs
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(X11 REQUIRED)
find_package(CURL REQUIRED)

# Include directories
include_directories(
    include 
    ${SDL2_INCLUDE_DIRS} 
    ${SDL2_TTF_INCLUDE_DIRS} 
    ${SDL2_IMAGE_INCLUDE_DIRS} 
    ${X11_INCLUDE_DIRS} 
    ${CURL_INCLUDE_DIRS}
    ${NLOHMANN_JSON_INCLUDE_DIRS}
    ${LUAJIT_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(
    ${PROJECT_NAME} 
    PRIVATE ${SDL2_LIBRARIES} 
    PRIVATE ${SDL2_TTF_LIBRARIES} 
    PRIVATE ${SDL2_IMAGE_LIBRARIES} 
    PRIVATE ${X11_LIBRARIES} 
    PRIVATE ${CURL_LIBRARIES}
    PRIVATE ${LUAJIT_LIBRARIES}
)
