//
// Created by Brandon on 5/20/2020.
//

#pragma once

#include <glm/vec3.hpp>

namespace VisualGlow
{
    class Camera
    {
    public:
        glm::vec3 position;
        glm::vec3 velocity;
        glm::vec3 acceleration;

        Camera(glm::vec3 position = glm::vec3(0.0, 0.0, 0.0), glm::vec3 velocity = glm::vec3(0.0, 0.0, 0.0), glm::vec3 acceleration = glm::vec3(0.0, 0.0, 0.0));

        void update(float dt);
    };
}