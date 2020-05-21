//
// Created by Brandon on 5/20/2020.
//

#pragma once

#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define VGLOW_OPENGL_MAJOR_VERSION_3 3
#define VGLOW_OPENGL_MINOR_VERSION_3 0

struct Configuration
{
    unsigned int width = 1920;
    unsigned int height = 1080;
    bool vsync = false;
    bool fullscreen = false;
    bool editorMode = false;
};

class VENGINE
{
private:
    Configuration configuration;
    GLFWwindow* windowInstance;

public:
    VENGINE(const Configuration& configuration, int majorVersion, int minorVersion);
    ~VENGINE();

    void Begin() const;
};