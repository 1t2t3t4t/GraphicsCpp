#pragma once

#include <glm/fwd.hpp>

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
    void setUniformV3(const char *name, float x, float y, float z) const;
    void setUniformMat4f(const char *name, glm::mat4 mat) const;
};
