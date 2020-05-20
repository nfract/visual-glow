//
// Created by Brandon on 5/19/2020.
//

#ifndef VISUAL_GLOW_PARAMETERS_H
#define VISUAL_GLOW_PARAMETERS_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace VisualGlow::Core
{
    struct Camera
    {
        glm::vec3 position   = glm::vec3(0.0f, 0.0f, -200.0f);
        glm::vec3 velocity   = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec2 resolution = glm::vec2(3340.0f, 1440.0f);
        float aspectRatio    = resolution.x / resolution.y;
    };

    struct WorldConfiguration
    {
        float maxHitDistance = 100.0f;
        float minHitDistance = 0.001f;
        float worldScale = 200.0f;
    };

    struct Characteristics
    {
        float distortion = .3f;
        float localizedDistortion = .2f;
        float interpolatedGlow = .8f;
    };

    struct Discrete
    {
        float rgb[3] = { .1f, .7f, 0.0f };
        float scale = 0.745f;
        float offset = 0.0f;
        float bias = 1.3f;
    };

    struct Indiscrete
    {
        float rgb[3] = { .1f, .7f, 0.0f };
        float scale = 15.6578f;
        float offset = 0.0f;
        float bias = .3f;
    };
}

#endif