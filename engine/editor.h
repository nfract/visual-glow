//
// Created by Brandon on 5/21/2020.
//

#pragma once

#include <GLFW/glfw3.h>

#include "camera.h"
#include "fractals/fractal.h"

class Editor
{
public:
    Editor(GLFWwindow* windowInstance);

    void Draw(Camera* camera, Fractal* fractal) const;

};