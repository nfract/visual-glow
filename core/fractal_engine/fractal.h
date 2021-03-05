//
// Created by Brandon on 5/20/2020.
//

#pragma once

#include <string>

#include "../opengl/shaders/opengl_shader_program.h"

class Fractal
{
protected:
    ShaderProgram* shader;

public:
    Fractal(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    {
        shader = new ShaderProgram(vertexShaderPath, fragmentShaderPath);
        shader->Bind();
    }

    virtual ~Fractal()
    {
        delete shader;
    }

    ShaderProgram* GetShader() { return shader; }

    virtual void RenderEditorModule() = 0;
    virtual void SendShaderData(const ShaderProgram& shaderProgram) const = 0;

    virtual void ReadBinaryFile(const std::string& filePath) = 0;
    virtual void WriteBinaryFile(const std::string& filePath) = 0;
};