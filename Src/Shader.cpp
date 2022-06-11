#include <glad/glad.h>
#include <string>
#include "Shader.h"
#include "FileSystem.h"

void ReportShaderCompileStatus(const unsigned int shaderId)
{
    int success;
    char infoLog[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void ReportLinkProgramStatus(const unsigned int program)
{
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }
}

void AddAndCompileSrc(const unsigned int id, const std::string& src)
{
    auto cSrc = src.c_str();
    glShaderSource(id, 1, &cSrc, nullptr);
    glCompileShader(id);
    ReportShaderCompileStatus(id);
}

Shader::Shader(const char *vertexShaderPath, const char *fragShaderPath)
{
    auto vertexShaderSrc = ReadFile(vertexShaderPath);
    auto fragShaderSrc = ReadFile(fragShaderPath);

    auto vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    AddAndCompileSrc(vertexShaderId, vertexShaderSrc);

    auto fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    AddAndCompileSrc(fragShaderId, fragShaderSrc);

    programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragShaderId);
    glLinkProgram(programId);
    ReportLinkProgramStatus(programId);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragShaderId);
}

void Shader::use() const
{
    glUseProgram(programId);
}

void Shader::setUniformF(const char *name, float value) const
{
    auto location = glGetUniformLocation(programId, name);
    if (location == -1)
    {
        std::cout << "Cannot find uniform location: " << name << std::endl;
    }
    glUniform1f(location, value);
}

