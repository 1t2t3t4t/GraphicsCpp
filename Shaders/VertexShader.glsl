#version 330

layout (location = 0) in vec3 aVertex;
layout (location = 1) in vec3 aColor;

out vec3 color;

uniform float hOffset;

void main()
{
    gl_Position = vec4(hOffset + aVertex.x , -aVertex.y, aVertex.z, 1.0);
    color = aColor;
}
