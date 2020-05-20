//
// Created by Brandon on 5/20/2020.
//

#include "opengl_context.h"

#include <vector>

#include "gui/opengl_imgui.h"
#include "shaders/shader_program.h"
#include "vertex_array_buffer.h"
#include "index_buffer.h"

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

        OPENGLIMGUI imgui(windowInstance);

        while (!glfwWindowShouldClose(windowInstance))
        {
            glfwPollEvents();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

            // RENDER IMGUI
            imgui.NewFrame();

            imgui.Render();

            // DRAW THE RECTANGLE TO THE SCREEN
            arrayBuffer.Bind();
            arrayBuffer.UnbindLayout(0);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            glfwSwapBuffers(windowInstance);
        }
    }
}