//
// Created by Brandon on 5/19/2020.
//

#include "window.h"

namespace VisualGlow::Core
{
    Window::Window(Renderer::RendererContext* rendererContext)
        : rendererContext(rendererContext)
    {
    }

    Window::~Window()
    {
        delete rendererContext;
    }

    void Window::start() const
    {
        rendererContext->begin();
    }
}