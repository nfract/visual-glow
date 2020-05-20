//
// Created by Brandon on 5/20/2020.
//

#include "opengl_context.h"

#include "../../core/constants.h"

namespace VisualGlow::Renderer
{
    OpenGLContext::OpenGLContext(int majorVersion, int minorVersion)
    {
        if (!glfwInit())
        {
            VGLOW_ERROR("could not initialize GLFW... does GLFW exists on the system?")
            std::exit(-1);
        }

        windowInstance = glfwCreateWindow(1920, 1080, "Visual Glow", nullptr, nullptr);
        glfwMakeContextCurrent(windowInstance);

        if (glewInit() != GLEW_OK)
        {
            VGLOW_ERROR("could not initialize GLEW... does GLEW exists on the system?")
            std::exit(-1);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);

        VGLOW_INFO("finished initializing GLEW")
        VGLOW_INFO("finished initializing GLFW with OpenGL version " << majorVersion << "." << minorVersion)
    }

    OpenGLContext::~OpenGLContext()
    {
        glfwDestroyWindow(windowInstance);
    }

    void OpenGLContext::begin() const
    {
        while (!glfwWindowShouldClose(windowInstance))
        {
            glfwPollEvents();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

            glfwSwapBuffers(windowInstance);
        }
    }
}