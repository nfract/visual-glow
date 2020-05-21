//
// Created by Brandon on 5/20/2020.
//

#include "vengine.h"

#include <chrono>
#include <vector>

#include "opengl/shaders/opengl_shader_program.h"
#include "opengl/opengl_vertex_array_buffer.h"
#include "opengl/opengl_index_buffer.h"

#include "editor.h"
#include "logging.h"
#include "fractals/discrete_fractal.h"

VENGINE::VENGINE(const Configuration& configuration, int majorVersion, int minorVersion)
    : configuration(configuration)
{
    if (!glfwInit())
    {
        VGLOW_ERR("could not initialize GLFW... does GLFW exists on the system?")
        std::exit(-1);
    }

    windowInstance = glfwCreateWindow(configuration.width, configuration.height, "Visual Glow", nullptr, nullptr);
    glfwMakeContextCurrent(windowInstance);

    if (glewInit() != GLEW_OK)
    {
        VGLOW_ERR("could not initialize GLEW... does GLEW exists on the system?")
        std::exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);

    VGLOW_INF("finished initializing GLEW")
    VGLOW_INF("finished initializing GLFW with OPENGL version " << majorVersion << "." << minorVersion)
}

VENGINE::~VENGINE()
{
    glfwDestroyWindow(windowInstance);
}

void VENGINE::Begin() const
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

    VertexArrayBuffer arrayBuffer;

    VertexBuffer buffer(vertices, 12);
    arrayBuffer.MapVertexBuffer(&buffer, layouts);

    IndexBuffer indexBuffer(indices, 6);

    ShaderProgram shaderProgram("shaders/vertex.glsl", "shaders/fragment.glsl");
    shaderProgram.Bind();

    Editor editor(windowInstance);
    DiscreteFractal discreteFractal;
    Camera camera;

    float dt = 0.0f;

    while (!glfwWindowShouldClose(windowInstance))
    {
        auto start = std::chrono::high_resolution_clock::now();
        glfwPollEvents();

        camera.Update(dt);

        // SEND SHADER DATA
        shaderProgram.UniformFloat("u_dt", dt);
        shaderProgram.UniformVec3("u_Resolution", glm::vec3(configuration.width, configuration.height, 0.0f));
        discreteFractal.SendShaderData(shaderProgram);
        camera.SendShaderData(shaderProgram);

        // OPENGL CLEAR BUFFER BIT ETC...
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // DRAW THE RECTANGLE TO THE SCREEN
        arrayBuffer.Bind();
        arrayBuffer.BindLayout(0);
        indexBuffer.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        // ALLOWS THE ABILITY TO QUICK SWITCH BETWEEN EDITOR MODE AND CAPTURE MODE
        if (configuration.editorMode)
            editor.Draw(&camera, &discreteFractal);

        glfwSwapBuffers(windowInstance);
        dt = std::chrono::duration<float, std::milli>(std::chrono::high_resolution_clock::now() - start).count();
    }
}