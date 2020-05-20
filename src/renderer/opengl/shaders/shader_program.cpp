//
// Created by Brandon on 5/18/2020.
//

#include "shader_program.h"

#include <GL/glew.h>
#include <GLM/gtc/type_ptr.hpp>

#include "../../../core/constants.h"

namespace VisualGlow::Renderer
{
    ShaderProgram::ShaderProgram(const std::string& vertexFile, const std::string& fragmentFile)
    {
        uint32_t vertexShaderID = Compile(GL_VERTEX_SHADER, read_file(vertexFile));
        uint32_t fragmentShaderID = Compile(GL_FRAGMENT_SHADER, read_file(fragmentFile));

        id = glCreateProgram();

        glAttachShader(id, vertexShaderID);
        glAttachShader(id, fragmentShaderID);

        glLinkProgram(id);
        glValidateProgram(id);

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);

        uniformCache = new std::unordered_map<std::string, unsigned int>();
    }

    ShaderProgram::~ShaderProgram()
    {
        delete uniformCache;
    }

    uint32_t ShaderProgram::Compile(uint32_t type, const std::string& shaderSource) const
    {
        uint32_t shaderID = glCreateShader(type);

        const char* cShaderSource = shaderSource.c_str();
        glShaderSource(shaderID, 1, &cShaderSource, 0);
        glCompileShader(shaderID);

        GLint isCompiled = 0;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(shaderID);

            switch (type)
            {
                case GL_VERTEX_SHADER:
                    VGLOW_ERROR("(vertex shader) " << infoLog.data());
                    break;

                case GL_FRAGMENT_SHADER:
                    VGLOW_ERROR("(fragment shader) " << infoLog.data());
                    break;
            }

            return -1;
        }

        return shaderID;
    }

    unsigned int ShaderProgram::LoadUniformLocation(const std::string& name) const
    {
        if (uniformCache->find(name) == uniformCache->end())
        {
            auto uniformLocation = glGetUniformLocation(id, name.c_str());
            uniformCache->emplace(name, uniformLocation);
        }

        return uniformCache->at(name);
    }

    void ShaderProgram::UniformMatrix4(const std::string& name, const glm::mat4& matrix) const
    {
        glUniformMatrix4fv(LoadUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void ShaderProgram::UniformVec3(const std::string& name, const glm::vec3& vec) const
    {
        glUniform3f(LoadUniformLocation(name), vec.x, vec.y, vec.z);
    }

    void ShaderProgram::UniformFloat(const std::string& name, float value) const
    {
        glUniform1f(LoadUniformLocation(name), value);
    }

    void ShaderProgram::Bind() const
    {
        glUseProgram(id);
    }

    void ShaderProgram::Unbind() const
    {
        glUseProgram(0);
    }
}