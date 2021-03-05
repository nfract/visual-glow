//
// Created by Brandon on 5/21/2020.
//

#include "editor.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw_gl3.h"
#include "../stb/stb_image_write.h"

#include "logging.h"

Editor::Editor(GLFWwindow* window_instance, PNGVideoEncoder* png_video_encoder, unsigned int width, unsigned int height)
    : window_instance(window_instance), png_video_encoder(png_video_encoder), width(width), height(height), project("init", "init")
{
    std::memset(text_buffer1, 0, 256);
    std::memset(text_buffer2, 0, 256);
    int_input1 = 0;
    int_input2 = 10;

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window_instance, true);
    ImGui::StyleColorsDark();
}

void Editor::Draw(Camera* camera, Fractal* fractal)
{
    ImGui_ImplGlfwGL3_NewFrame();

    unsigned int file_menu_action = 0;
    unsigned int project_menu_action = 0;
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open Project..."))    file_menu_action = 2;
            if (ImGui::MenuItem("Save"))
            {
                project.WriteSettings();
                fractal->WriteBinaryFile(project.GetCombinedFractalPath());

                glfwSetWindowTitle(window_instance, project.GetName().c_str());
                std::memset(text_buffer1, 0, 256);
                std::memset(text_buffer2, 0, 256);
            }
            if (ImGui::MenuItem("Save Project As...")) file_menu_action = 3;

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Project"))
        {
            if (ImGui::MenuItem("Take Screenshot"))
            {
                char *data = (char*) malloc((size_t) (width * height * 3));
                glPixelStorei(GL_PACK_ALIGNMENT, 1);
                glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

                std::stringstream stream;
                stream << project.GetFolderPath() << "/screenshots/" << "sh_" << get_time_milliseconds() << ".png";
                stbi_write_png(stream.str().c_str(), width, height, 3, data, 0);
            }

            if (ImGui::MenuItem("Record Video")) project_menu_action = 1;
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if (file_menu_action == 2) ImGui::OpenPopup("Open Project...");
    if (file_menu_action == 3) ImGui::OpenPopup("Save Project As...");

    if (ImGui::BeginPopup("Open Project..."))
    {
        ImGui::Text("Open Project...");
        ImGui::InputText("Project Path", text_buffer1, 256);
        if (ImGui::Button("Open"))
        {
            std::stringstream settings_stream;
            settings_stream << std::string(text_buffer1) << "/settings.a";
            project.SetFolderPath(std::string(text_buffer1));
            project.ReadFromSettings(settings_stream.str());

            fractal->ReadBinaryFile(project.GetCombinedFractalPath());

            glfwSetWindowTitle(window_instance, project.GetName().c_str());
            std::memset(text_buffer1, 0, 256);

            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
            ImGui::CloseCurrentPopup();

        ImGui::EndPopup();
    }

    if (ImGui::BeginPopup("Save Project As..."))
    {
        ImGui::Text("Save Project As...");
        ImGui::InputText("Project Name", text_buffer1, 256);
        ImGui::InputText("Project Path", text_buffer2, 256);
        if (ImGui::Button("Save"))
        {
            project.SetName(std::string(text_buffer1));
            project.SetFolderPath(std::string(text_buffer2));
            project.WriteSettings();

            fractal->WriteBinaryFile(project.GetCombinedFractalPath());

            glfwSetWindowTitle(window_instance, project.GetName().c_str());
            std::memset(text_buffer1, 0, 256);
            std::memset(text_buffer2, 0, 256);

            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    if (project_menu_action == 1) ImGui::OpenPopup("Record Video");

    if (ImGui::BeginPopup("Record Video"))
    {
        ImGui::Text("Record Video");

        ImGui::SliderInt("Frame Quantity", &int_input1, 1, 900);
        ImGui::SliderInt("Frame Rate", &int_input2, 10, 120);
        if (ImGui::Button("Start"))
        {
            png_video_encoder->StartEncode(int_input1, int_input2);
            int_input1 = 0;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    fractal->RenderEditorModule();
    camera->RenderEditorModule();

    ImGui::Render();
    ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

const Project& Editor::GetProject() const
{
    return project;
}