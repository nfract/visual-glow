//
// Created by Brandon on 5/20/2020.
//

#include "renderer.h"

#include <chrono>
#include <vector>

#include "opengl/shaders/opengl_shader_program.h"
#include "opengl/opengl_vertex_array_buffer.h"
#include "opengl/opengl_index_buffer.h"

#include "editor.h"
#include "logging.h"
#include "png_video_encoder.h"
#include "fractal_engine/y2k_fractal.h"

Renderer::Renderer(const Configuration& configuration, int major_version, int minor_version)
    : configuration(configuration)
{
    if (!glfwInit())
    {
        SOFTX86_ERR("could not initialize GLFW... does GLFW exists on the system?")
        std::exit(-1);
    }

    window_instance = glfwCreateWindow(configuration.width, configuration.height, "softx86", nullptr, nullptr);
    glfwMakeContextCurrent(window_instance);

    if (glewInit() != GLEW_OK)
    {
        SOFTX86_ERR("could not initialize GLEW... does GLEW exists on the system?")
        std::exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);

    glfwSwapInterval(configuration.vsync);
    SOFTX86_INF("finished initializing GLEW")
    SOFTX86_INF("finished initializing GLFW with OPENGL version " << major_version << "." << minor_version)
}

Renderer::~Renderer()
{
    glfwDestroyWindow(window_instance);
}

void Renderer::Begin()
{
    // DISPLAY RECTANGLE VERTICES
    float vertices[12] =
    {
        -1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
         1.0f, -1.0f, 0.0f
    };

    // DISPLAY RECTANGLE INDICES
    unsigned int indices[6] =
    {
        0, 1, 2, 2, 3, 0
    };

    std::vector<VertexArrayLayout> layouts;
    layouts.emplace_back(3, 3, 0);

    VertexArrayBuffer array_buffer;

    VertexBuffer buffer(vertices, 12);
    array_buffer.MapVertexBuffer(&buffer, layouts);

    IndexBuffer index_buffer(indices, 6);

    PNGVideoEncoder png_video_encoder(&configuration);

    Editor editor(window_instance, &png_video_encoder, configuration.width, configuration.height);
    Y2KFractal y2kFractalEngine;
    Camera camera;

    float dt = 0.0f;
    while (!glfwWindowShouldClose(window_instance))
    {
        auto start = std::chrono::high_resolution_clock::now();

        glfwPollEvents();

        if (configuration.live_render)
            camera.Update(dt / 100);
        else
            camera.Update((1.0f / configuration.encoder_frame_rate));

        // SEND SHADER DATA
        y2kFractalEngine.GetShader()->UniformFloat("u_dt", dt);
        y2kFractalEngine.GetShader()->UniformVec3("u_Resolution", glm::vec3(configuration.width, configuration.height, 0.0f));
        y2kFractalEngine.SendShaderData(*y2kFractalEngine.GetShader());
        camera.SendShaderData(*y2kFractalEngine.GetShader());

        // OPENGL CLEAR BUFFER BIT ETC...
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // DRAW THE RECTANGLE TO THE SCREEN
        array_buffer.Bind();
        array_buffer.BindLayout(0);
        index_buffer.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        png_video_encoder.PrepareNext(editor.GetProject().GetFolderPath());

        // ALLOWS THE ABILITY TO QUICK SWITCH BETWEEN EDITOR MODE AND CAPTURE MODE
        if (configuration.editor_mode)
            editor.Draw(&camera, &y2kFractalEngine);

        glfwSwapBuffers(window_instance);
        dt = std::chrono::duration<float, std::milli>(std::chrono::high_resolution_clock::now() - start).count();
    }
}

void Renderer::LiveRender()
{}