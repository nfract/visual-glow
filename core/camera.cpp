//
// Created by Brandon on 5/20/2020.
//

#include "camera.h"

#include "../imgui/imgui.h"

#include "logging.h"

Camera::Camera(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration, float maximum_hit_distance, float minimum_hit_distance)
        : position(position), velocity(velocity), acceleration(acceleration), maximum_hit_distance(maximum_hit_distance), minimum_hit_distance(minimum_hit_distance)
{}

void Camera::Update(float dt)
{
    position += velocity * dt + 0.5f * acceleration * dt * dt;
}

void Camera::RenderEditorModule()
{
    if (ImGui::Begin("Camera"))
    {
        ImGui::Text("Hit Distance");
        ImGui::SliderFloat("Maximum", &maximum_hit_distance, 0.0f, 1000.0f);
        ImGui::SliderFloat("Minimum", &minimum_hit_distance, 0.001f, 0.00001f);

        ImGui::Separator();
        ImGui::Text("Position");
        ImGui::SliderFloat("X", &position.x, -500.0f, 500.0f);
        ImGui::SliderFloat("Y", &position.y, -500.0f, 500.0f);
        ImGui::SliderFloat("Z", &position.z, -500.0f, 500.0f);
        if (ImGui::Button("Reset X/Y/Z"))
            position = glm::vec3(0.0f, 0.0f, 0.0f);

        ImGui::Separator();
        ImGui::Text("Velocity");
        ImGui::SliderFloat("DX", &velocity.x, -10.0f, 10.0f);
        ImGui::SliderFloat("DY", &velocity.y, -10.0f, 10.0f);
        ImGui::SliderFloat("DZ", &velocity.z, -10.0f, 10.0f);
        if (ImGui::Button("Reset DX/DY/DZ"))
            velocity = glm::vec3(0.0f, 0.0f, 0.0f);

        ImGui::Separator();
        ImGui::Text("Acceleration");
        ImGui::SliderFloat("D2X", &acceleration.x, -0.3f, 0.3f);
        ImGui::SliderFloat("D2Y", &acceleration.y, -0.3f, 0.3f);
        ImGui::SliderFloat("D2Z", &acceleration.z, -0.3f, 0.3f);
        if (ImGui::Button("Reset D2X/D2Y/D2Z"))
            acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

        ImGui::End();
    }
}

void Camera::SendShaderData(const ShaderProgram &shaderProgram) const
{
    shaderProgram.UniformFloat("u_MaxHitDistance", maximum_hit_distance);
    shaderProgram.UniformFloat("u_MinHitDistance", minimum_hit_distance);
    shaderProgram.UniformVec3("u_CameraPosition",  glm::vec3(position.x, position.y, position.z));
}