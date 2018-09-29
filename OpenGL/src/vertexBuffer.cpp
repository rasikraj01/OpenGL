//
//  vertexBuffer.cpp
//  OpenGL
//
//  Created by Rasik Raj on 29/09/18.
//  Copyright © 2018 Rasik Raj. All rights reserved.
//

#include "vertexBuffer.hpp"

#include "renderer.hpp"

#include <iostream>

VertexBuffer::VertexBuffer(const void* data, unsigned int size){
    glGenBuffers(1, &m_Render_ID); // this generates a buffer and gives the id to the unsigned int buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_Render_ID); // selecting that buffer
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);// fill the buffer with data
    
}
VertexBuffer::~VertexBuffer(){
    glDeleteBuffers(1, &m_Render_ID);
}

void VertexBuffer::Bind() const{
    glBindBuffer(GL_ARRAY_BUFFER, m_Render_ID);
}

void VertexBuffer::ubBind() const{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
