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

file(GLOB_RECURSE SOURCES "core/*.cpp" "core/*.h" "imgui/*.h" "imgui/*.cpp" "main/*.cpp" "main/*.h")

add_compile_definitions(GLEW_STATIC)
add_compile_definitions(STB_IMAGE_WRITE_IMPLEMENTATION)
add_compile_definitions(STB_IMAGE_WRITE_STATIC)
add_executable(visual_glow ${SOURCES} core/opengl/shaders/opengl_shader_program.cpp core/camera.cpp core/renderer.cpp core/camera.h core/fractal_engine/y2k_fractal.h core/fractal_engine/y2k_fractal.cpp core/fractal_engine/fractal.h core/editor.cpp core/editor.h core/logging.h stb/stb_image_write.h core/project.cpp core/project.h core/png_video_encoder.cpp core/png_video_encoder.h core/configuration.h)
target_include_directories(visual_glow PUBLIC ${STATIC_LIBRARY_INCLUDES})
target_link_libraries(visual_glow ${STATIC_LIBRARIES})