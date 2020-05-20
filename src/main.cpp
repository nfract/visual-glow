//
// Created by Brandon on 5/18/2020.
//

#include "renderer/opengl/opengl_context.h"
#include "core/window.h"

int main()
{
    VisualGlow::WindowConfiguration configuration;
    configuration.width      = 1920;
    configuration.height     = 1080;
    configuration.fullscreen = false;
    configuration.vsync      = false;

    VisualGlow::OpenGLContext openGL(configuration, VGLOW_OPENGL_MAJOR_VERSION_3, VGLOW_OPENGL_MINOR_VERSION_3);

    VisualGlow::Window window(configuration, openGL);
    window.Start();

    return 0;
}