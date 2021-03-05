//
// Created by Brandon on 5/18/2020.
//

#include "opengl_vertex_array_buffer.h"

#include <GL/glew.h>

VertexArrayBuffer::VertexArrayBuffer()
{
    glGenVertexArrays(1, &id);
    Bind();
}

VertexArrayBuffer::~VertexArrayBuffer()
{
    glDeleteVertexArrays(1, &id);
}

void VertexArrayBuffer::MapVertexBuffer(VertexBuffer* vertexBuffer, const std::vector<VertexArrayLayout>& layouts) const
{
    vertexBuffer->Bind();

    auto internalIndexer = 0;
    for (auto layout : layouts)
    {
        glEnableVertexAttribArray(internalIndexer);
        glVertexAttribPointer(internalIndexer, layout.size, GL_FLOAT, GL_FALSE, sizeof(float) * layout.stride, (void*) layout.offset);
        glDisableVertexAttribArray(internalIndexer);
        internalIndexer++;
    }

    vertexBuffer->Unbind();
}

void VertexArrayBuffer::BindLayout(unsigned int index) const
{
    glEnableVertexAttribArray(index);
}

void VertexArrayBuffer::UnbindLayout(unsigned int index) const
{
    glDisableVertexAttribArray(index);
}

void VertexArrayBuffer::Bind() const
{
    glBindVertexArray(id);
}

void VertexArrayBuffer::Unbind() const
{
    glBindVertexArray(0);
}