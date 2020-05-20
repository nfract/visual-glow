//
// Created by Brandon on 5/20/2020.
//

#include "opengl_context.h"

#include <chrono>
#include <vector>

#include "gui/opengl_imgui.h"
#include "shaders/shader_program.h"
#include "vertex_array_buffer.h"
#include "index_buffer.h"

#include "../camera.h"
#include "../fractals/discrete_fractal.h"
#include "../../imgui/imgui.h"
#include "../../core/constants.h"

namespace VisualGlow
{
    OpenGLContext::OpenGLContext(WindowConfiguration& windowConfiguration, int majorVersion, int minorVersion)
        : RendererContext(windowConfiguration)
    {
        if (!glfwInit())
        {
            VGLOW_ERROR("could not initialize GLFW... does GLFW exists on the system?")
            std::exit(-1);
        }

        windowInstance = glfwCreateWindow(windowConfiguration.width, windowConfiguration.height, "Visual Glow", nullptr, nullptr);
        glfwMakeContextCurrent(windowInstance);

        if (glewInit() != GLEW_OK)
        {
            VGLOW_ERROR("could not initialize GLEW... does GLEW exists on the system?")
            std::exit(-1);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);

        VGLOW_INFO("finished initializing GLEW")
        VGLOW_INFO("finished initializing GLFW with OPENGL version " << majorVersion << "." << minorVersion)
    }

    OpenGLContext::~OpenGLContext()
    {
        glfwDestroyWindow(windowInstance);
    }

    void OpenGLContext::Begin() const
    {
        // DISPLAY RECTANGLE VERTICIES
        float vertices[12] =
        {
                -1.0f, -1.0f, 0.0f,
                -1.0f,  1.0f, 0.0f,
                1.0f,   1.0f, 0.0f,
                1.0f,  -1.0f, 0.0f
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

        OPENGLIMGUI imgui(windowInstance);
        DiscreteFractal discreteFractal;
        Camera camera;

        float dt = 0.0f;

        while (!glfwWindowShouldClose(windowInstance))
        {
            // POLL FOR EVENTS AND START MEASURING DT
            auto start = std::chrono::high_resolution_clock::now();
            glfwPollEvents();

            // UPDATE THE CAMERA DUH
            camera.Update(dt);

            // SEND SHADER DATA
            shaderProgram.UniformFloat("u_dt", dt);
            shaderProgram.UniformVec3("u_Resolution", glm::vec3(windowConfiguration.width, windowConfiguration.height, 0.0f));
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

            // RENDER IMGUI
            imgui.NewFrame();
            discreteFractal.RenderEditorModule();
            camera.RenderEditorModule();
            imgui.Render();

            glfwSwapBuffers(windowInstance);
            dt = std::chrono::duration<float, std::milli>(std::chrono::high_resolution_clock::now() - start).count();
        }
    }
}