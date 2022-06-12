#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "stb_image.h"

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

unsigned char *LoadImage(const char *name, int *w, int *h, int *nrChannel)
{
    return stbi_load(name, w, h, nrChannel, 0);
}

void FreeImage(unsigned char *data)
{
    stbi_image_free(data);
}