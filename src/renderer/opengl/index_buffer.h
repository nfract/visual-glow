//
// Created by Brandon on 5/18/2020.
//

#ifndef VISUAL_GLOW_INDEX_BUFFER_H
#define VISUAL_GLOW_INDEX_BUFFER_H

namespace VisualGlow::Graphics
{
    class IndexBuffer
    {
    private:
        unsigned int id;
        unsigned int size;

    public:
        IndexBuffer(unsigned int* data, unsigned int size);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;
    };
}

#endif