#ifndef indexBuffer_hpp
#define indexBuffer_hpp

#include <stdio.h>

#endif

class IndexBuffer{
private:
    unsigned int m_Render_ID;
    unsigned int m_Count;
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();
    
    void Bind() const;
    void ubBind() const;
    inline unsigned int GetCount() const { return m_Count;};

};
