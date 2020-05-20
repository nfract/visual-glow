//
// Created by Brandon on 5/18/2020.
//

#include "renderer/opengl/opengl_context.h"
#include "core/window.h"

int main()
{
    VisualGlow::Renderer::OpenGLContext openGL(3, 0);

    VisualGlow::Core::Window window(&openGL);
    window.start();

    return 0;
}