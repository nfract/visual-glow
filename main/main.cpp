//
// Created by Brandon on 5/18/2020.
//

#include "../engine/vengine.h"

int main()
{
    Configuration configuration;
    configuration.width      = 1920;
    configuration.height     = 1080;
    configuration.fullscreen = false;
    configuration.vsync      = false;
    configuration.editorMode = true;

    VENGINE vengine(configuration, VGLOW_OPENGL_MAJOR_VERSION_3, VGLOW_OPENGL_MINOR_VERSION_3);
    vengine.Begin();

    return 0;
}