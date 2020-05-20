//
// Created by Brandon on 5/20/2020.
//

#pragma once

#include "../opengl/shaders/shader_program.h"

namespace VisualGlow
{
    class Fractal
    {
    public:
        virtual void RenderEditor() = 0;
        virtual void SendShaderData(const ShaderProgram& shaderProgram) const = 0;
    };
}