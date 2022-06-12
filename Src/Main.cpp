#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "FileSystem.h"

void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

const float Vertices[] = {
        // pos        // texCoords
        -0.5, 0.5, 0, 0, 1, // tl
        0.5, 0.5, 0, 1, 1, // tr
        -0.5, -0.5, 0, 0, 0, // bl
        0.5, -0.5, 0, 1, 0 // br
};

const unsigned int Indices[] = {
        0, 1, 2,
        1, 3, 2
};

GLFWwindow *CreateWindow()
{
    const int res = glfwInit();
    if (res != GLFW_TRUE)
    {
        std::cout << "Failed to init glfw" << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For Mac machine

    GLFWwindow *window = glfwCreateWindow(800, 600, "Graphics", nullptr, nullptr);
    if (window == nullptr)
    {
        const char *description;
        auto err = glfwGetError(&description);
        printf("Failed to init gl window %d\n%s", err, description);
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    return window;
}

void ProcessInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    GLFWwindow *window = CreateWindow();

    // Init VAO, VBO, EBO
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    // Init Shader
    Shader shader("Shaders/VertexShader.glsl", "Shaders/FragShader.glsl");

    // Init Texture
    unsigned int faceTextureId;
    glGenTextures(1, &faceTextureId);
    glBindTexture(GL_TEXTURE_2D, faceTextureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int w, h, nrChannel;
    auto faceTexture = LoadImage("Assets/awesomeface.png", &w, &h, &nrChannel);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, faceTexture);
    glGenerateMipmap(GL_TEXTURE_2D);
    FreeImage(faceTexture);

    if (window == nullptr)
    {
        return -1;
    }

    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);

        // Clear screen to grayish color
        glClearColor(.3f, .3f, .3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw
        shader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
