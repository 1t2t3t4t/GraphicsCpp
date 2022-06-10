#pragma once

#include <glad/glad.h>

const float Vertices[] = {
        -0.5, -0.5, 0, // btl
        0.5, -0.5, 0, // btr
        0.5, 0.5, 0, // tr
        -0.5, 0.5, 0 //tl
};

const unsigned int Indices[] = {
        0, 1, 2,
        3, 2, 0
};

const char *VertexShader = "#version 330 core\n"
                           "layout (location = 0) in vec3 aPos;\n"
                           "void main()\n"
                           "{\n"
                           "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                           "}";
const char *FragmentShader = "#version 330 core\n"
                             "out vec4 FragColor;\n"
                             "void main()\n"
                             "{\n"
                             "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                             "}";

void CompileShader(const unsigned int vertexShaderId, const unsigned  int fragmentShaderId)
{
    glShaderSource(vertexShaderId, 1, &VertexShader, nullptr);
    glCompileShader(vertexShaderId);

    glShaderSource(fragmentShaderId, 1, &FragmentShader, nullptr);
    glCompileShader(fragmentShaderId);
}


void Update()
{
    // Send rectangle vertices to VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    // Send rectangle indices to EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}