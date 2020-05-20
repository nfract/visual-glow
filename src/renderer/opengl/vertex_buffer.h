//
// Created by Brandon on 5/18/2020.
//

#pragma once

namespace VisualGlow::Renderer
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