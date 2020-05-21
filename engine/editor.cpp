//
// Created by Brandon on 5/21/2020.
//

#include "editor.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw_gl3.h"

Editor::Editor(GLFWwindow* windowInstance)
{
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(windowInstance, true);
    ImGui::StyleColorsDark();
}

void Editor::Draw(Camera* camera, Fractal* fractal) const
{
    ImGui_ImplGlfwGL3_NewFrame();

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open..."))
            {

            } else
            {

            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    fractal->RenderEditorModule();
    camera->RenderEditorModule();

    ImGui::Render();
    ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}