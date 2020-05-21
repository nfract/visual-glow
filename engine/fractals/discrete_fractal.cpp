//
// Created by Brandon on 5/20/2020.
//

#include "discrete_fractal.h"

#include <iostream>
#include <stdio.h>

#include "../logging.h"
#include "../../imgui/imgui.h"

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

void DiscreteFractal::ReadBinaryFile(const std::string& filePath)
{
    FILE* filePoint;

    if (fopen_s(&filePoint, filePath.c_str(), "rb") != 0)
    {
        VGLOW_ERR("could not open file point " << filePath << " for reading")
        return;
    }

    fread(&interpolation.highDistortion, 1, sizeof(float), filePoint);
    fread(&interpolation.lowDistortion,  1, sizeof(float), filePoint);
    fread(&interpolation.discreteGlow,   1, sizeof(float), filePoint);

    for (int i = 0; i < 3; i++)
        fread(&topVolume.rgb[i], 1, sizeof(float), filePoint);

    fread(&topVolume.scale,  1, sizeof(float), filePoint);
    fread(&topVolume.offset, 1, sizeof(float), filePoint);
    fread(&topVolume.bias,   1, sizeof(float), filePoint);

    for (int i = 0; i < 3; i++)
        fread(&bottomVolume.rgb[i], 1, sizeof(float), filePoint);

    fread(&bottomVolume.scale,  1, sizeof(float), filePoint);
    fread(&bottomVolume.offset, 1, sizeof(float), filePoint);
    fread(&bottomVolume.bias,   1, sizeof(float), filePoint);

    for (int i = 0; i < 3; i++)
        fread(&combinationVolume.rgb[i], 1, sizeof(float), filePoint);

    fread(&combinationVolume.multplier,  1, sizeof(float), filePoint);
    fread(&combinationVolume.thickness, 1, sizeof(float), filePoint);

    fclose(filePoint);
}

void DiscreteFractal::WriteBinaryFile(const std::string& filePath)
{
    FILE* filePoint;

    if (fopen_s(&filePoint, filePath.c_str(), "wb") != 0)
    {
        VGLOW_ERR("could not open file point " << filePath << " for writing")
        return;
    }

    fwrite(&interpolation.highDistortion, 1, sizeof(float), filePoint);
    fwrite(&interpolation.lowDistortion,  1, sizeof(float), filePoint);
    fwrite(&interpolation.discreteGlow,   1, sizeof(float), filePoint);

    for (int i = 0; i < 3; i++)
        fwrite(&topVolume.rgb[i], 1, sizeof(float), filePoint);

    fwrite(&topVolume.scale,  1, sizeof(float), filePoint);
    fwrite(&topVolume.offset, 1, sizeof(float), filePoint);
    fwrite(&topVolume.bias,   1, sizeof(float), filePoint);

    for (int i = 0; i < 3; i++)
        fwrite(&bottomVolume.rgb[i], 1, sizeof(float), filePoint);

    fwrite(&bottomVolume.scale,  1, sizeof(float), filePoint);
    fwrite(&bottomVolume.offset, 1, sizeof(float), filePoint);
    fwrite(&bottomVolume.bias,   1, sizeof(float), filePoint);

    for (int i = 0; i < 3; i++)
        fwrite(&combinationVolume.rgb[i], 1, sizeof(float), filePoint);

    fwrite(&combinationVolume.multplier,  1, sizeof(float), filePoint);
    fwrite(&combinationVolume.thickness, 1, sizeof(float), filePoint);

    fclose(filePoint);
}