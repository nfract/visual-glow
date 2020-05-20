//
// Created by Brandon on 5/18/2020.
//

#ifndef VISUAL_GLOW_VERTEX_BUFFER_H
#define VISUAL_GLOW_VERTEX_BUFFER_H

namespace VisualGlow::Graphics
{
    class VertexBuffer
    {
    private:
        unsigned int id;
        unsigned int size;

    public:
        VertexBuffer(float* data, unsigned int size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;
    };
}

#endif