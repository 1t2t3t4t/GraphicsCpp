#include <iostream>
#include <GLFW/glfw3.h>
#include "Mutex.h"

int main()
{
    Mutex mRes;
    auto handle = mRes.Lock();

    const int res = glfwInit();
    std::cout << "Hello World!" << std::endl;
    return 0;
}