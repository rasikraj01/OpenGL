//
//  vertexBuffer.hpp
//  OpenGL
//
//  Created by Rasik Raj on 29/09/18.
//  Copyright © 2018 Rasik Raj. All rights reserved.
//

#ifndef vertexBuffer_hpp
#define vertexBuffer_hpp

#include <stdio.h>

#endif /* vertexBuffer_hpp */


class VertexBuffer{
private:
    unsigned int m_Render_ID;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();
    
    void Bind() const;
    void ubBind() const;
    
};
