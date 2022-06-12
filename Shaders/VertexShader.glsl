#version 330

layout (location = 0) in vec3 aVertex;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aVertex.x , aVertex.y, aVertex.z, 1.0);
    TexCoord = aTexCoord;
}
