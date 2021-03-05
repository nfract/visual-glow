//
// Created by Brandon on 3/5/2021.
//

#include "project.h"

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <filesystem>

#include "logging.h"

Project::Project(const std::string &folder_path, const std::string &name)
    : folder_path(folder_path), name(name)
{}

void Project::WriteSettings()
{
    std::filesystem::create_directories(folder_path);
    std::filesystem::create_directories(folder_path + "/screenshots");
    std::filesystem::create_directories(folder_path + "/video");

    FILE* file_point;
    std::string combined_path = GetCombinedSettingsPath();

    if (fopen_s(&file_point, combined_path.c_str(), "wb") != 0)
    {
        SOFTX86_ERR("could not open file point " << combined_path << " for writing")
        return;
    }

    fputs(name.c_str(), file_point);

    fclose(file_point);
}

void Project::ReadFromSettings(const std::string &settings_file_path)
{
    std::filesystem::create_directories(folder_path);
    std::filesystem::create_directories(folder_path + "/screenshots");
    std::filesystem::create_directories(folder_path + "/video");

    FILE* file_point;

    if (fopen_s(&file_point, settings_file_path.c_str(), "rb") != 0)
    {
        SOFTX86_ERR("could not open file point " << settings_file_path << " for reading")
        return;
    }

    char name_buf[256];
    fgets(name_buf, 256, file_point);
    name = std::string(name_buf);

    fclose(file_point);
}

void Project::SetFolderPath(const std::string &new_folder_path)
{
    folder_path = new_folder_path;
}

void Project::SetName(const std::string &new_name)
{
    name = new_name;
}

std::string Project::GetFolderPath() const
{
    return folder_path;
}

std::string Project::GetName() const
{
    return name;
}

std::string Project::GetCombinedSettingsPath() const
{
    std::stringstream stream;
    stream << folder_path << "/" << "settings.a";

    return stream.str();
}

std::string Project::GetCombinedFractalPath() const
{
    std::stringstream stream;
    stream << folder_path << "/" << "fractal.b";

    return stream.str();
}