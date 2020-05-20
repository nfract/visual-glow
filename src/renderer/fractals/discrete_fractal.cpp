//
// Created by Brandon on 5/20/2020.
//

#include "discrete_fractal.h"

#include "../../imgui/imgui.h"

namespace VisualGlow
{
    void DiscreteFractal::RenderEditorModule()
    {
        ImGui::Begin("Discrete Fractal");

        if (ImGui::CollapsingHeader("Interpolation"))
        {
            ImGui::SliderFloat("High Distortion", &interpolation.highDistortion, 0.0f, 10.0f);
            ImGui::SliderFloat("Low Distortion", &interpolation.lowDistortion, 0.0f, 10.0f);
            ImGui::SliderFloat("Discrete Glow", &interpolation.discreteGlow, 0.0f, 1.1f);
        }

        ImGui::Separator();

        if (ImGui::CollapsingHeader("Top Volume"))
        {
            ImGui::ColorEdit3("Top Volume Color",    topVolume.rgb, 0);
            ImGui::SliderFloat("Top Volume Scale",  &topVolume.scale, 0.0f, 5.0f);
            ImGui::SliderFloat("Top Volume Offset", &topVolume.offset, 0.0, 0.1f);
            ImGui::SliderFloat("Top Volume Bias",   &topVolume.bias, 0.0, 5.0f);
        }

        ImGui::Separator();

        if (ImGui::CollapsingHeader("Bottom Volume"))
        {
            ImGui::ColorEdit3("Bottom Volume Color",    bottomVolume.rgb, 0);
            ImGui::SliderFloat("Bottom Volume Scale",  &bottomVolume.scale, 0.0f, 15.0f);
            ImGui::SliderFloat("Bottom Volume Offset", &bottomVolume.offset, 0.0, 5.0f);
            ImGui::SliderFloat("Bottom Volume Bias",   &bottomVolume.bias, 0.0, 15.0f);
        }

        ImGui::Separator();

        if (ImGui::CollapsingHeader("Combination Volume"))
        {
            ImGui::ColorEdit3("Combination Volume Color",         combinationVolume.rgb, 0);
            ImGui::SliderFloat("Combination Volume Multiplier",  &combinationVolume.multplier, 0.0f, 15.0f);
            ImGui::SliderFloat("Combination Volume Thickness",   &combinationVolume.thickness, 0.0, 15.0f);
        }

        ImGui::End();
    }

    void DiscreteFractal::SendShaderData(const ShaderProgram &shaderProgram) const
    {
        shaderProgram.UniformFloat("u_HighDistortion", interpolation.highDistortion);
        shaderProgram.UniformFloat("u_LowDistortion",  interpolation.lowDistortion);
        shaderProgram.UniformFloat("u_DiscreteGlow",   interpolation.discreteGlow);

        shaderProgram.UniformVec3("u_TopVolumeColor",   glm::vec3(topVolume.rgb[0], topVolume.rgb[1], topVolume.rgb[2]));
        shaderProgram.UniformFloat("u_TopVolumeScale",  topVolume.scale);
        shaderProgram.UniformFloat("u_TopVolumeOffset", topVolume.offset);
        shaderProgram.UniformFloat("u_TopVolumeBias",   topVolume.bias);

        shaderProgram.UniformVec3("u_BottomVolumeColor",   glm::vec3(bottomVolume.rgb[0], bottomVolume.rgb[1], bottomVolume.rgb[2]));
        shaderProgram.UniformFloat("u_BottomVolumeScale",  bottomVolume.scale);
        shaderProgram.UniformFloat("u_BottomVolumeOffset", bottomVolume.offset);
        shaderProgram.UniformFloat("u_BottomVolumeBias",   bottomVolume.bias);

        shaderProgram.UniformVec3("u_CombinationVolumeColor",   glm::vec3(combinationVolume.rgb[0], combinationVolume.rgb[1], combinationVolume.rgb[2]));
        shaderProgram.UniformFloat("u_CombinationVolumeMultiplier",  combinationVolume.multplier);
        shaderProgram.UniformFloat("u_CombinationVolumeThickness", combinationVolume.thickness);
    }
}