//
// Created by Brandon on 5/19/2020.
//

#include "window.h"

namespace VisualGlow
{
    Window::Window(WindowConfiguration& windowConfiguration, const RendererContext& rendererContext)
        : windowConfiguration(windowConfiguration), rendererContext(rendererContext)
    {
    }

    Window::~Window()
    {
    }

    void Window::Start() const
    {
        rendererContext.Begin();
    }
}