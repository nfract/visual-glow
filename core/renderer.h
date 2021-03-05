//
// Created by Brandon on 5/20/2020.
//

#pragma once

#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "configuration.h"

#define SOFTX86_OPENGL_MAJOR_VERSION_3 3
#define SOFTX86_OPENGL_MINOR_VERSION_3 0


class Renderer
{
private:
    Configuration configuration;
    GLFWwindow* window_instance;

public:
    Renderer(const Configuration& configuration, int major_version, int minor_version);
    ~Renderer();

    void Begin();
    void LiveRender();
    void EncoderRender();
};