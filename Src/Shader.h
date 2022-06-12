#pragma once

class Shader
{
private:
    unsigned int programId;

public:
    Shader(const char* vertexShaderPath, const char* fragShaderPath);

    unsigned int GetId() const 
    {
        return programId;
    }

    void use() const;

    void setUniformI(const char *name, int value) const;
    void setUniformF(const char *name, float value) const;
};
