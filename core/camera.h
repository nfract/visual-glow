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

    float maximum_hit_distance;
    float minimum_hit_distance;

    Camera(glm::vec3 position = glm::vec3(0.0, 0.0, 0.0), glm::vec3 velocity = glm::vec3(0.0, 0.0, 0.0), glm::vec3 acceleration = glm::vec3(0.0, 0.0, 0.0), float maximum_hit_distance = 100.0f, float minimum_hit_distance = 0.001f);

    void Update(float dt);
    void RenderEditorModule();
    void SendShaderData(const ShaderProgram& shader_program) const;
};