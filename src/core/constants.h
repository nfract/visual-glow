//
// Created by Brandon on 5/18/2020.
//

#ifndef VISUAL_GLOW_CONSTANTS_H
#define VISUAL_GLOW_CONSTANTS_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#define VGLOW_INFO(x)   std::cout << "vg_info:  "  << x << std::endl;
#define VGLOW_ERROR(x) std::cout << "vg_error: " << x << std::endl;

namespace VisualGlow
{
    inline std::string read_file(const std::string& path)
    {
        std::stringstream stream;
        std::string line;

        std::ifstream fileHandle(path);
        if (!fileHandle.is_open())
        {
            VGLOW_ERROR("could not read file " << path << "!")
            return "";
        }

        while (getline(fileHandle, line))
            stream << line << "\n";

        return stream.str();
    }
}

#endif