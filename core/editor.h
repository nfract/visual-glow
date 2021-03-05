//
// Created by Brandon on 5/21/2020.
//

#pragma once

#include <GLFW/glfw3.h>

#include "project.h"
#include "camera.h"
#include "png_video_encoder.h"
#include "fractal_engine/fractal.h"

class Editor
{
private:
    GLFWwindow* window_instance;
    PNGVideoEncoder* png_video_encoder;
    unsigned int width;
    unsigned int height;

    char text_buffer1[256];
    char text_buffer2[256];
    int int_input1;
    int int_input2;

    Project project;

public:
    Editor(GLFWwindow* window_instance, PNGVideoEncoder* png_video_encoder, unsigned int width, unsigned int height);

    void Draw(Camera* camera, Fractal* fractal);

    const Project& GetProject() const;
};