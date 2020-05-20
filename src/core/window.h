//
// Created by Brandon on 5/19/2020.
//

#pragma once

#include "../renderer/renderer_context.h"

namespace VisualGlow
{
    class Window
    {
    private:
        WindowConfiguration& windowConfiguration;
        const RendererContext& rendererContext;

    public:
        Window(WindowConfiguration& windowConfiguration, const RendererContext& rendererContext);
        ~Window();

        void Start() const;
    };
}