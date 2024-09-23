cmake_minimum_required(VERSION 3.10)

project(SimpleGFX VERSION 1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(external/glm)
add_subdirectory(external/glfw)

set(EXAMPLES 
    ${CMAKE_CURRENT_SOURCE_DIR}/examples/hello_world.cpp
)

# Temporary solution
file(GLOB_RECURSE SOURCES 
    src/glad.c
    src/*.cpp
)

add_library(simple_gfx STATIC ${SOURCES})

target_link_libraries(simple_gfx PUBLIC glm glfw GL)

target_include_directories(simple_gfx PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    external/glm
    external/glfw/include
    external/
)

file(GLOB_RECURSE EXAMPLES examples/*.cpp)

foreach(EXAMPLE_FILE ${EXAMPLES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_FILE} NAME_WE)
    
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_FILE})
    
    target_link_libraries(${EXAMPLE_NAME} PRIVATE simple_gfx)
    
    set_target_properties(${EXAMPLE_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
endforeach()
