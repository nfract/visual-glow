//
// Created by Brandon on 5/20/2020.
//

#include "opengl_imgui.h"

#include "../../../imgui/imgui.h"
#include "../../../imgui/imgui_impl_glfw_gl3.h"

#include "../../../core/constants.h"

namespace VisualGlow
{
    OPENGLIMGUI::OPENGLIMGUI(GLFWwindow* windowInstance)
    {
        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(windowInstance, true);
        ImGui::StyleColorsDark();

        VGLOW_INFO("succesfully attached IMGUI to GLFW OPENGL instance")
    }

    void OPENGLIMGUI::NewFrame() const
    {
        ImGui_ImplGlfwGL3_NewFrame();
    }

    void OPENGLIMGUI::Render() const
    {
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
    }
}