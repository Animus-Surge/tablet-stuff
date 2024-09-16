cmake_minimum_required(VERSION 3.10)

# Make clangd work with cmake
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(pda_tablet VERSION 1.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Get sources
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# Move resources directory to output directory
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# Build mode checks
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE PDA_DEBUG)
endif()

# External libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(include ${SDL2_INCLUDE_DIRS} ${SDL2_ttf_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_ttf_LIBRARIES})
