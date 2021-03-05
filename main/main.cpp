//
// Created by Brandon on 5/18/2020.
//

#include "../core/renderer.h"

int main()
{
    Configuration configuration;
    configuration.width      = 1920;
    configuration.height     = 1080;
    configuration.fullscreen = false;
    configuration.vsync      = true;
    configuration.editor_mode = true;

    Renderer renderer(configuration, SOFTX86_OPENGL_MAJOR_VERSION_3, SOFTX86_OPENGL_MINOR_VERSION_3);
    renderer.Begin();

    return 0;
}