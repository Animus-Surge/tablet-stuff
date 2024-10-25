cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(
    project(PDAGraphResearch VERSION 1.0)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED True)

    file(GLOB_RECURSE SOURCES "src/*.cpp")
    add_executable(${PROJECT_NAME} ${SOURCES})

    find_package(SDL2 REQUIRED)

    include_directories(include ${SDL2_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
