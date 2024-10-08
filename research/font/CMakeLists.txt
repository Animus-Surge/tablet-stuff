cmake_minimum_required(VERSION 3.10)

# Make clangd work with cmake
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/scripts/cmake/")

project(PDAFontResearch VERSION 1.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Get sources
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

find_package(SDL2 REQUIRED)
find_package(spdlog REQUIRED)

include_directories(include ${spdlog_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${spdlog_LIBRARIES} ${SDL2_LIBRARIES})
