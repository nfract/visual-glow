//
// Created by Brandon on 5/18/2020.
//

#pragma once

#include <vector>

#include "vertex_buffer.h"

namespace VisualGlow::Renderer
{
    struct VertexArrayLayout
    {
        unsigned int size;
        unsigned int stride;
        unsigned int offset;

        VertexArrayLayout(unsigned int size, unsigned int stride, unsigned int offset)
            : size(size), stride(stride), offset(offset)
        {}
    };

    class VertexArrayBuffer
    {
    private:
        unsigned int id;

    public:
        VertexArrayBuffer();
        ~VertexArrayBuffer();

        void MapVertexBuffer(VertexBuffer* vertexBuffer, const std::vector<VertexArrayLayout>& layouts) const;

        void BindLayout(unsigned int index) const;
        void UnbindLayout(unsigned int index) const;
        void Bind() const;
        void Unbind() const;
    };
}