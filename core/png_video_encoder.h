//
// Created by Brandon on 3/5/2021.
//

#pragma once

#include <string>

#include "configuration.h"

class PNGVideoEncoder
{
private:
    bool currently_encoding;
    unsigned int internal_clock;
    unsigned int amount_to_write;

    Configuration* configuration;

public:
    PNGVideoEncoder(Configuration* configuration);

    void StartEncode(unsigned int amount_to_encode, unsigned int frame_rate);
    void PrepareNext(const std::string& project_folder_path);
    void Encode(const std::string& project_folder_path);
};