//
// Created by Brandon on 5/18/2020.
//

#include "vertex_buffer.h"

#include <GL/glew.h>

namespace VisualGlow::Graphics
{
    VertexBuffer::VertexBuffer(float* data, unsigned int size)
        : size(size)
    {
        glCreateBuffers(1, &id);
        Bind();

        // BUFFER THE DATA
        glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &id);
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}