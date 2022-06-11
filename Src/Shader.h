#pragma once

class Shader
{
private:
    unsigned int programId;

public:
    Shader(const char* vertexShaderPath, const char* fragShaderPath);

    void use() const;
};
