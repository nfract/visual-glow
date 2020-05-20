//
// Created by Brandon on 5/18/2020.
//

#include "index_buffer.h"

#include <GL/glew.h>

namespace VisualGlow::Graphics
{
    IndexBuffer::IndexBuffer(unsigned int *data, unsigned int size)
        : size(size)
    {
        glCreateBuffers(1, &id);
        Bind();

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(unsigned int), data, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &id);
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void IndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}