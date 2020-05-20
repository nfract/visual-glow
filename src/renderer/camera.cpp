//
// Created by Brandon on 5/20/2020.
//

#include "camera.h"

namespace VisualGlow
{
    Camera::Camera(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration)
        : position(position), velocity(velocity), acceleration(acceleration)
    {
    }

    void Camera::update(float dt)
    {
        position.x += velocity.x * dt + .5f * acceleration.x * acceleration.x;
        position.y += velocity.y * dt + .5f * acceleration.y * acceleration.y;
        position.z += velocity.z * dt + .5f * acceleration.z * acceleration.z;
    }
}