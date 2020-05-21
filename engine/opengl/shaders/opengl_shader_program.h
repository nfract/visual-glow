//
// Created by Brandon on 5/18/2020.
//

#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>

#include <glm/matrix.hpp>

class ShaderProgram
{
private:
    unsigned int id;

    std::unordered_map<std::string, unsigned int>* uniformCache;

public:
    ShaderProgram(const std::string& vertexFile, const std::string& fragmentFile);
    ~ShaderProgram();

    [[nodiscard]] unsigned int LoadUniformLocation(const std::string& name) const;
    void UniformMatrix4(const std::string& name, const glm::mat4& matrix = glm::mat4(1.0f)) const;
    void UniformVec3(const std::string& name, const glm::vec3& vec = glm::vec3(0.0f)) const;
    void UniformFloat(const std::string& name, float value) const;

    void Bind() const;
    void Unbind() const;

private:
    [[nodiscard]] unsigned int Compile(unsigned int type, const std::string& shaderSource) const;
    [[nodiscard]] std::string ReadFile(const std::string& filePath) const;
};