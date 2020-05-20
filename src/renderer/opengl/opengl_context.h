//
// Created by Brandon on 5/20/2020.
//

#pragma once

#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../renderer_context.h"

namespace VisualGlow::Renderer
{
    class OpenGLContext : public RendererContext
    {
    private:
        GLFWwindow* windowInstance;

    public:
        OpenGLContext(int majorVersion, int minorVersion);
        ~OpenGLContext();

        void begin() const override;

    };
}