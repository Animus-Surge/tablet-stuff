# JSONcpp libs and include dir located in ${PROJECT_SOURCE_DIR}/external/jsoncpp/build/lib and ${PROJECT_SOURCE_DIR}/external/jsoncpp/include

if(NOT TARGET jsoncpp_lib)
    add_library(jsoncpp_lib STATIC IMPORTED)
    set_target_properties(jsoncpp_lib PROPERTIES
        IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/jsoncpp/build/lib/libjsoncpp.a
        INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/jsoncpp/include
    )
endif()

# Add the include directories for the jsoncpp library
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/jsoncpp/include)

# Link the jsoncpp library to the project
target_link_libraries(${PROJECT_NAME} jsoncpp_lib)

