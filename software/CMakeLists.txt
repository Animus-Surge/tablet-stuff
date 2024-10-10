cmake_minimum_required(VERSION 3.10)

# Make clangd work with cmake
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/scripts/cmake/")

project(pda_tablet VERSION 1.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Get sources
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# Move resources directory to output directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)

# Build mode checks
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE PDA_DEBUG)
endif()

# External libraries (TODO: toolchain paths)
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(X11 REQUIRED)

message(STATUS "SDL2_ttf as SDL2_TTF_LIBRARY: ${SDL2_TTF_LIBRARY}")
message(STATUS "SDL2_ttf as SDL2_TTF_LIBRARIES: ${SDL2_TTF_LIBRARIES}")

include_directories(include ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})
