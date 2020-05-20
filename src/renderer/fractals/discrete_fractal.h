//
// Created by Brandon on 5/20/2020.
//

#pragma once

#include "fractal.h"

namespace VisualGlow
{
    class DiscreteFractal : public Fractal
    {
        struct Interpolation
        {
            float highDistortion = .3f;
            float lowDistortion  = .2f;
            float discreteGlow   = .8f;
        };

        struct TopVolume
        {
            float rgb[3] = { .1f, .7f, 0.0f };
            float scale  = 0.745f;
            float offset = 0.0f;
            float bias   = 1.3f;
        };

        struct BottomVolume
        {
            float rgb[3] = { .1f, .7f, 0.0f };
            float scale  = 0.745f;
            float offset = 0.0f;
            float bias   = 1.3f;
        };

    private:
        Interpolation interpolation;
        TopVolume     topVolume;
        BottomVolume  bottomVolume;

    public:
        void RenderEditor() override;
        void SendShaderData(const ShaderProgram& shaderProgram) const override;
    };
}