//
// Created by Brandon on 5/18/2020.
//

#pragma once

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