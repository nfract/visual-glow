//
// Created by Brandon on 5/19/2020.
//

#pragma once

#include "../renderer/renderer_context.h"

namespace VisualGlow::Core
{
    class Window
    {
    private:
        Renderer::RendererContext* rendererContext;

    public:
        Window(Renderer::RendererContext* rendererContext);
        ~Window();

        void start() const;
    };
}