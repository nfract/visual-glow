//
// Created by Brandon on 5/20/2020.
//

#pragma once

#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../renderer_context.h"

#define VGLOW_OPENGL_MAJOR_VERSION_3 3
#define VGLOW_OPENGL_MINOR_VERSION_3 0

namespace VisualGlow
{
    class OpenGLContext : public RendererContext
    {
    private:
        GLFWwindow* windowInstance;

    public:
        OpenGLContext(WindowConfiguration& windowConfiguration, int majorVersion, int minorVersion);
        ~OpenGLContext();

        void Begin() const override;

    };
}