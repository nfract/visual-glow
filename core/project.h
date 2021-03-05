//
// Created by Brandon on 3/5/2021.
//

#pragma once


#include <string>

class Project
{
private:
    std::string folder_path;
    std::string name;

public:
    Project(const std::string& folder_path, const std::string& name);

    void WriteSettings();
    void ReadFromSettings(const std::string& settings_file_path);

    void SetFolderPath(const std::string& new_folder_path);
    void SetName(const std::string& new_name);

    std::string GetFolderPath() const;
    std::string GetName() const;
    std::string GetCombinedSettingsPath() const;
    std::string GetCombinedFractalPath() const;
};