//
// Created by Brandon on 5/20/2020.
//

#pragma once

#include <string>

#include "../opengl/shaders/opengl_shader_program.h"

class Fractal
{
public:
    virtual void RenderEditorModule() = 0;
    virtual void SendShaderData(const ShaderProgram& shaderProgram) const = 0;

    virtual void ReadBinaryFile(const std::string& filePath) = 0;
    virtual void WriteBinaryFile(const std::string& filePath) = 0;
};