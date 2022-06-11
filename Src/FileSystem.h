#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

std::string ReadFile(const char *fileName)
{
    std::ifstream file(fileName);
    std::string output;
    if (file.is_open())
    {
        std::stringstream fileStream;
        fileStream << file.rdbuf();
        output = fileStream.str();
        file.close();
    }

    return output;
}
