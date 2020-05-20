//
// Created by Brandon on 5/20/2020.
//

#pragma once

namespace VisualGlow::Renderer
{
    class RendererContext
    {
    public:
        virtual void begin() const = 0;
    };
}