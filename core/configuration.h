//
// Created by Brandon on 3/5/2021.
//

#pragma once

struct Configuration
{
    unsigned int width = 1920;
    unsigned int height = 1080;
    bool vsync = false;
    bool fullscreen = false;
    bool editor_mode = true;
    bool live_render = true;
    float encoder_frame_rate = 30.0f;
};