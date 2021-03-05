//
// Created by Brandon on 3/5/2021.
//

#include "png_video_encoder.h"

#include <sstream>
#include <GLFW/glfw3.h>

#include "logging.h"

#include "../stb/stb_image_write.h"

PNGVideoEncoder::PNGVideoEncoder(Configuration* configuration)
    : configuration(configuration), currently_encoding(false), internal_clock(0), amount_to_write(0)
{}

void PNGVideoEncoder::StartEncode(unsigned int amount_to_encode, unsigned int frame_rate)
{
    amount_to_write = amount_to_encode;
    currently_encoding = true;
    configuration->editor_mode = false;
    configuration->live_render = false;
    configuration->encoder_frame_rate = frame_rate;
}

void PNGVideoEncoder::PrepareNext(const std::string& project_folder_path)
{
    if (currently_encoding)
    {
        if (internal_clock <= amount_to_write)
            Encode(project_folder_path);
        else
        {
            currently_encoding = false;
            configuration->editor_mode = true;
            configuration->live_render = true;
        }

        internal_clock++;
    }
    else
    {
        internal_clock = 0;
    }
}

void PNGVideoEncoder::Encode(const std::string& project_folder_path)
{
    char *data = (char*) malloc((size_t) (configuration->width * configuration->height* 3));
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, configuration->width, configuration->height, GL_RGB, GL_UNSIGNED_BYTE, data);

    std::stringstream stream;
    stream << project_folder_path << "/video/" << internal_clock << ".png";

    stbi_flip_vertically_on_write(true);
    stbi_write_png(stream.str().c_str(), configuration->width, configuration->height, 3, data, 0);

    SOFTX86_INF("PNG ENCODER wrote frame " << internal_clock << " for " << project_folder_path << "/video")
}