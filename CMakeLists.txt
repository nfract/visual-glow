cmake_minimum_required(VERSION 3.16)
project(visual_glow)

if (WIN32)
    # Window Library Links
    set(STATIC_LIBRARIES glfw3.lib glew32s.lib opengl32.lib)
    set(STATIC_LIBRARY_INCLUDES ${CMAKE_SOURCE_DIR}\\libraries\\includes)
    link_directories(${CMAKE_SOURCE_DIR}\\libraries)
else()
    # Linux Library Links
endif()

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCESS "src/*.cpp" "src/*.hpp")

add_compile_definitions(GLEW_STATIC)
add_executable(visual_glow ${SOURCESS} src/core/parameters.h)
target_include_directories(visual_glow PUBLIC ${STATIC_LIBRARY_INCLUDES})
target_link_libraries(visual_glow ${STATIC_LIBRARIES})