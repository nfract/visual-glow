//
// Created by Brandon on 5/18/2020.
//

#include <iostream>
#include <chrono>

#include "__imgui/imgui.h"
#include "__imgui/imgui_impl_glfw_gl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "graphics/opengl/shaders/shader_program.h"
#include "graphics/opengl/vertex_array_buffer.h"
#include "graphics/opengl/index_buffer.h"
#include "core/constants.h"

#include <fstream>

using namespace glm;
using namespace VisualGlow::Graphics;

int main()
{
    if (!glfwInit())
    {
        std::cout << "Failed to load glfw" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Visual Glow", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize glew" << std::endl;
        return -1;
    }

    glfwSwapInterval(1);

    float vertices[12] =
    {
                    -1.0f, -1.0f, 0.0f,
                    -1.0f, 1.0f, 0.0f,
                    1.0f, 1.0f, 0.0f,
                    1.0f, -1.0f, 0.0f
    };

    unsigned int indices[6] =
    {
                    0, 1, 2, 2, 3, 0
    };

    ShaderProgram shaders("shaders/vertex.glsl", "shaders/fragment.glsl");
    shaders.Bind();

    std::vector<VertexArrayLayout> layouts;
    layouts.emplace_back( 3, 3, 0 );

    VertexArrayBuffer arrayBuffer;

    VertexBuffer buffer(vertices, 12);
    arrayBuffer.MapVertexBuffer(&buffer, layouts);

    IndexBuffer indexBuffer(indices, 6);

    float dt = 0;
    auto start = std::chrono::high_resolution_clock::now();

    float itime = 0;

    mat4 viewMatrix = lookAt(vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0));

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    vec3 cameraPosition = vec3(0.0f, 0.0f, -500.0f);
    vec3 cameraVelocity = vec3(0.0f, 0.0f, 0.0f);

    vec3 resolution = vec3(1920.0f, 1080.0f, 1920.0f / 1080.0f);

    float maxHitDistance= 100.0f;
    float minHitDistance = 0.001f;
    float worldScale = 200.0f;

    float balance1 = .3f;
    float balance2 = .2f;
    float distanceBalance = .8f;

    float discreteRgb[3] = { .1f, .7f, 0.0f } ;
    float discreteScale = 0.745f;
    float discreteOffset = 0.0f;
    float discreteBias = 1.3f;

    float inDiscreteRgb[3] = { .1f, .7f, 0.0f } ;
    float inDiscreteScale = 15.6578f;
    float inDiscreteOffset = 0.0f;
    float inDiscreteBias = .3f;

    char* fileName = new char[256];
    std::memset(fileName, 0, 256);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        ImGui_ImplGlfwGL3_NewFrame();

        arrayBuffer.Bind();
        arrayBuffer.BindLayout(0);
        indexBuffer.Bind();

        shaders.UniformFloat("dt", dt);
        shaders.UniformFloat("itime", itime);
        shaders.UniformMatrix4("viewMatrix", viewMatrix);

        shaders.UniformVec3("u_Resolution", resolution);

        shaders.UniformVec3("u_CameraPosition", vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z));
        shaders.UniformVec3("u_CameraVelocity", vec3(cameraVelocity.x, cameraVelocity.y, cameraVelocity.z));

        shaders.UniformFloat("u_MaxHitDistance", maxHitDistance);
        shaders.UniformFloat("u_MinHitDistance", minHitDistance);
        shaders.UniformFloat("u_WorldScale", worldScale);

        shaders.UniformFloat("u_Balance1", balance1);
        shaders.UniformFloat("u_Balance2", balance2);
        shaders.UniformFloat("u_DistanceBalance", distanceBalance);

        shaders.UniformVec3("u_DiscreteColor", vec3(discreteRgb[0], discreteRgb[1], discreteRgb[2]));
        shaders.UniformFloat("u_DiscreteScale", discreteScale);
        shaders.UniformFloat("u_DiscreteOffset", discreteOffset);
        shaders.UniformFloat("u_DiscreteBias", discreteBias);

        shaders.UniformVec3("u_IndiscreteColor", vec3(inDiscreteRgb[0], inDiscreteRgb[1], inDiscreteRgb[2]));
        shaders.UniformFloat("u_IndiscreteScale", inDiscreteScale);
        shaders.UniformFloat("u_IndiscreteOffset", inDiscreteOffset);
        shaders.UniformFloat("u_IndiscreteBias", inDiscreteBias);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        ImGui::Begin("Processing");

        if (ImGui::CollapsingHeader("Camera"))
        {
            ImGui::SliderFloat("Camera X", &cameraPosition.x, -500.0f, 500.0f);
            ImGui::SliderFloat("Camera Y", &cameraPosition.y, -500.0f, 500.0f);
            ImGui::SliderFloat("Camera Z", &cameraPosition.z, -500.0f, 500.0f);
            ImGui::SliderFloat("Camera VX", &cameraVelocity.x, -1.0f, 1.0f);
            ImGui::SliderFloat("Camera VY", &cameraVelocity.y, -1.0f, 1.0f);
            ImGui::SliderFloat("Camera VZ", &cameraVelocity.z, -1.0f, 1.0f);
            if (ImGui::Button("Reset Position"))
            {
                cameraPosition = vec3(0.0f, 0.0f, -500.0f);
            }
            if (ImGui::Button("Reset Velocity"))
            {
                cameraVelocity = vec3(0.0f, 0.0f, 0.0f);
            }
        }

        ImGui::Separator();

        if (ImGui::CollapsingHeader("World Properties"))
        {
            ImGui::Text("General -");
            ImGui::InputFloat("Maximum Hit Distance", &maxHitDistance);
            ImGui::InputFloat("Minimum Hit Distance", &minHitDistance);
            ImGui::InputFloat("World Scale (Radius)", &worldScale);
        }

        ImGui::Separator();

        if (ImGui::CollapsingHeader("Characteristic(S)"))
        {
            ImGui::Text("Characteristic(s)");
            ImGui::SliderFloat("Distortion", &balance1, 0.0f, 2.5f);
            ImGui::SliderFloat("Engraved Distortion", &balance2, 0.0f, 2.5f);
            ImGui::SliderFloat("Interpolated Glow", &distanceBalance, 0.0f, 1.1f);
        }

        ImGui::Separator();

        if (ImGui::CollapsingHeader("Discrete"))
        {
            ImGui::Text("Discrete -");
            ImGui::ColorEdit3("Discrete Color", discreteRgb, 0);
            ImGui::SliderFloat("Discrete Scale", &discreteScale, 0.0f, 5.0f);
            ImGui::SliderFloat("Discrete Offset", &discreteOffset, 0.0, 0.1f);
            ImGui::SliderFloat("Discrete Bias", &discreteBias, 0.0, 5.0f);
        }

        ImGui::Separator();

        if (ImGui::CollapsingHeader("Indiscrete"))
        {
            ImGui::Text("Indiscrete -");
            ImGui::ColorEdit3("Indiscrete Color", inDiscreteRgb, 0);
            ImGui::SliderFloat("Indiscrete Scale", &inDiscreteScale, 0.0f, 20.0f);
            ImGui::SliderFloat("Indiscrete Offset", &inDiscreteOffset, 0.0, 0.1f);
            ImGui::SliderFloat("Indiscrete Bias", &inDiscreteBias, 0.0, 5.0f);
        }

        ImGui::End();

        ImGui::Begin("Load / Save");
        ImGui::InputText("File Name", fileName, 256);
        if (ImGui::Button("Load..."))
        {
            std::fstream loadFile("fractals/" + std::string(fileName));

            loadFile >> balance1;
            loadFile >> balance2;
            loadFile >> distanceBalance;
            loadFile >> discreteRgb[0];
            loadFile >> discreteRgb[1];
            loadFile >> discreteRgb[2];
            loadFile >> discreteScale;
            loadFile >> discreteOffset;
            loadFile >> discreteBias;
            loadFile >> inDiscreteRgb[0];
            loadFile >> inDiscreteRgb[1];
            loadFile >> inDiscreteRgb[2];
            loadFile >> inDiscreteScale;
            loadFile >> inDiscreteOffset;
            loadFile >> inDiscreteBias;

            VGLOW_LOG("loaded fractal " << std::string(fileName));
            loadFile.close();
        }

        if (ImGui::Button("Save..."))
        {
            std::ofstream saveFile("fractals/" + std::string(fileName));
            saveFile << balance1 << "\n";
            saveFile << balance2 << "\n";
            saveFile << distanceBalance << "\n";
            saveFile << discreteRgb[0] <<  "\n";
            saveFile << discreteRgb[1] <<  "\n";
            saveFile << discreteRgb[2] <<  "\n";
            saveFile << discreteScale << "\n";
            saveFile << discreteOffset << "\n";
            saveFile << discreteBias << "\n";
            saveFile << inDiscreteRgb[0] <<  "\n";
            saveFile << inDiscreteRgb[1] <<  "\n";
            saveFile << inDiscreteRgb[2] <<  "\n";
            saveFile << inDiscreteScale << "\n";
            saveFile << inDiscreteOffset << "\n";
            saveFile << inDiscreteBias;

            VGLOW_LOG("saved fractal " << std::string(fileName));
            saveFile.close();
        }

        if (ImGui::TreeNode("Test"))
        {
            ImGui::TreePop();
        }

        ImGui::End();

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        glfwPollEvents();
        glfwSwapBuffers(window);

        cameraPosition += cameraVelocity * (dt / 70000.0f);

        dt = std::chrono::duration<float, std::milli>(std::chrono::high_resolution_clock::now() - start).count();
        itime += 0.05f;
    }

    return 0;
}