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
uniform vec4 fragColor;
void main()
{
color = fragColor;
}
