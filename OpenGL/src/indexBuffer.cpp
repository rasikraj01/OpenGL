//
//  indexBuffer.cpp
//  OpenGL
//
//  Created by Rasik Raj on 29/09/18.
//  Copyright © 2018 Rasik Raj. All rights reserved.
//

#include "indexBuffer.hpp"

#include "renderer.hpp"

#include <iostream>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    :m_Count(count)
{
    glGenBuffers(1, &m_Render_ID); // this generates a buffer and gives the id to the unsigned int buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Render_ID); // selecting that buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);// fill the buffer with data
    
}
IndexBuffer::~IndexBuffer(){
    glDeleteBuffers(1, &m_Render_ID);
}

void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Render_ID);
}

void IndexBuffer::ubBind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
