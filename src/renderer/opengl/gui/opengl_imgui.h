//
// Created by Brandon on 5/20/2020.
//

#pragma once

#include <GLFW/glfw3.h>

namespace VisualGlow
{
    class OPENGLIMGUI
    {
    public:
        OPENGLIMGUI(GLFWwindow* windowInstance);

    public:
        void NewFrame() const;
        void Render() const;
    };
}