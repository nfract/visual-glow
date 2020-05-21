//
// Created by Brandon on 5/20/2020.
//

#pragma once

#include <glm/vec3.hpp>

#include "opengl/shaders/opengl_shader_program.h"

class Camera
{
public:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;

    float maximumHitDistance;
    float minimumHitDistance;

    Camera(glm::vec3 position = glm::vec3(0.0, 0.0, 0.0), glm::vec3 velocity = glm::vec3(0.0, 0.0, 0.0), glm::vec3 acceleration = glm::vec3(0.0, 0.0, 0.0), float maximumHitDistance = 100.0f, float minimumHitDistance = 0.001f);

    void Update(float dt);
    void RenderEditorModule();
    void SendShaderData(const ShaderProgram& shaderProgram) const;
};