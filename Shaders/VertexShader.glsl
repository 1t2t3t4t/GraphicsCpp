#version 330

layout (location = 0) in vec3 aVertex;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 Color;
out vec2 TexCoord;

uniform float hOffset;

void main()
{
    gl_Position = vec4(hOffset + aVertex.x , -aVertex.y, aVertex.z, 1.0);
    Color = aColor;
    TexCoord = aTexCoord;
}
