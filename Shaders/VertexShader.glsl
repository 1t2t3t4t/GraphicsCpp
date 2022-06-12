#version 330

layout (location = 0) in vec3 aVertex;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 Transform;

void main()
{
    gl_Position = Transform * vec4(aVertex, 1.0);
    TexCoord = aTexCoord;
}
