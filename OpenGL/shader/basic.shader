#shader Vertex

#version 330 core
layout (location = 0) in vec4 position;
void main()
{
gl_Position = position;
}


#shader Fragment
#version 330 core
out vec4 color;
void main()
{
color = vec4(0.7f, 0.5f, 0.6f, 1.0f);
}
