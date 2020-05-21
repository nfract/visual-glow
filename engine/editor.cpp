//
// Created by Brandon on 5/21/2020.
//

#include "editor.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw_gl3.h"

#include "logging.h"

Editor::Editor(GLFWwindow* windowInstance)
{
    std::memset(textBuffer, 0, 256);

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(windowInstance, true);
    ImGui::StyleColorsDark();
}

void Editor::Draw(Camera* camera, Fractal* fractal)
{
    ImGui_ImplGlfwGL3_NewFrame();

    ImGui::Begin("General");
    ImGui::Text("Save & Load");
    ImGui::InputText("File Path", textBuffer, 256);
    if (ImGui::Button("Open..."))
    {
        std::string strBuffer(textBuffer);
        fractal->ReadBinaryFile(std::string(textBuffer));
        VGLOW_INF("loaded fractal " << strBuffer)
    }

    ImGui::SameLine();
    if (ImGui::Button("Save..."))
    {
        std::string strBuffer(textBuffer);
        fractal->WriteBinaryFile(std::string(textBuffer));
        VGLOW_INF("saved fractal to " << strBuffer)
    }

    ImGui::Separator();
    ImGui::Text("World");

    ImGui::End();

    fractal->RenderEditorModule();
    camera->RenderEditorModule();

    ImGui::Render();
    ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}