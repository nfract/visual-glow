cmake_minimum_required(VERSION 3.16)
project(visual_glow)

if (WIN32)
    # Window Library Links
    set(STATIC_LIBRARIES glfw3.lib glew32s.lib opengl32.lib)
    set(STATIC_LIBRARY_INCLUDES ${CMAKE_SOURCE_DIR}\\thirdparty\\includes)
    link_directories(${CMAKE_SOURCE_DIR}\\thirdparty)
else()
    # Linux Library Links
endif()

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES "engine/*.cpp" "engine/*.h" "imgui/*.h" "imgui/*.cpp" "main/*.cpp" "main/*.h")

add_compile_definitions(GLEW_STATIC)
add_executable(visual_glow ${SOURCES} engine/opengl/shaders/opengl_shader_program.cpp engine/camera.cpp engine/vengine.cpp engine/camera.h engine/fractals/discrete_fractal.h engine/fractals/discrete_fractal.cpp engine/fractals/fractal.h engine/editor.cpp engine/editor.h engine/logging.h)
target_include_directories(visual_glow PUBLIC ${STATIC_LIBRARY_INCLUDES})
target_link_libraries(visual_glow ${STATIC_LIBRARIES})