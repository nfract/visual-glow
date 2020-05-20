//
// Created by Brandon on 5/20/2020.
//

#pragma once

#include "../core/window_configuration.h"

namespace VisualGlow
{
    class RendererContext
    {
    protected:
        WindowConfiguration& windowConfiguration;

    public:
        RendererContext(WindowConfiguration& windowConfiguration)
            : windowConfiguration(windowConfiguration)
        {}

        virtual void Begin() const = 0;
    };
}