//
// Created by Brandon on 5/20/2020.
//

#include "camera.h"

#include "../imgui/imgui.h"

namespace VisualGlow
{
    Camera::Camera(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration, float maximumHitDistance, float minimumHitDistance)
        : position(position), velocity(velocity), acceleration(acceleration), maximumHitDistance(maximumHitDistance), minimumHitDistance(minimumHitDistance)
    {
    }

    void Camera::Update(float dt)
    {
        dt /= 1000.0f;
        position.x += velocity.x * dt + .5f * acceleration.x * acceleration.x;
        position.y += velocity.y * dt + .5f * acceleration.y * acceleration.y;
        position.z += velocity.z * dt + .5f * acceleration.z * acceleration.z;
    }

    void Camera::RenderEditorModule()
    {
        ImGui::Begin("Camera");

        ImGui::SliderFloat("X", &position.x, -500.0f, 500.0f);
        ImGui::SliderFloat("Y", &position.y, -500.0f, 500.0f);
        ImGui::SliderFloat("Z", &position.z, -500.0f, 500.0f);
        if (ImGui::Button("Reset X/Y/Z"))
        {
            position = glm::vec3(0.0f, 0.0f, 0.0f);
        }

        ImGui::Separator();
        ImGui::SliderFloat("DX", &velocity.x, -1.0f, 1.0f);
        ImGui::SliderFloat("DY", &velocity.y, -1.0f, 1.0f);
        ImGui::SliderFloat("DZ", &velocity.z, -1.0f, 1.0f);
        if (ImGui::Button("Reset DX/DY/DZ"))
        {
            velocity = glm::vec3(0.0f, 0.0f, 0.0f);
        }

        ImGui::Separator();
        ImGui::SliderFloat("D2X", &acceleration.x, -0.3f, 0.3f);
        ImGui::SliderFloat("D2Y", &acceleration.y, -0.3f, 0.3f);
        ImGui::SliderFloat("D2Z", &acceleration.z, -0.3f, 0.3f);
        if (ImGui::Button("Reset D2X/D2Y/D2Z"))
        {
            acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
        }

        ImGui::End();
    }

    void Camera::SendShaderData(const ShaderProgram &shaderProgram) const
    {
        shaderProgram.UniformFloat("u_MaxHitDistance", maximumHitDistance);
        shaderProgram.UniformFloat("u_MinHitDistance", minimumHitDistance);
        shaderProgram.UniformVec3("u_CameraPosition", glm::vec3(position.x, position.y, position.z));
    }
}