#version 330

layout (location = 0) in vec3 aVertex;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 Transform;
uniform mat4 ViewTransform;
uniform mat4 ProjectionTransform;

void main()
{
    gl_Position = ProjectionTransform * ViewTransform * Transform * vec4(aVertex, 1.0);
    TexCoord = aTexCoord;
}
