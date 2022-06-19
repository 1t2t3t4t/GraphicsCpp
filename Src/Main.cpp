#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "FileSystem.h"
#include "MathUtils.h"
#include "Rotator.h"

void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

float Vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

const unsigned int Indices[] = {
        0, 1, 2,
        1, 3, 2
};

glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
};

float TextureVal = 0.f;
glm::vec3 camPos(0.f, 0.f, 3.f);
Rotator camRot;
glm::vec3 camUp(0.f, 1.f, 0.f);
float camSpeed = 5.f;
float LastX = 400;
float LastY = 300;
float Sensitivity = 0.1f;

bool FirstMouseCallback = true;
void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    auto offSetX = xPos - LastX;
    auto offSetY = LastY - yPos;
    LastX = (float)xPos;
    LastY = (float)yPos;

    if (FirstMouseCallback)
    {
        FirstMouseCallback = false;
        return;
    }

    offSetX *= Sensitivity;
    offSetY *= Sensitivity;

    camRot.Pitch += (float)offSetY;
    camRot.Yaw += (float)offSetX;

    camRot.Pitch = MathUtils::Clamp(camRot.Pitch, -89.f, 89.f);
}

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
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, MouseCallback);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    return window;
}

void ProcessInput(GLFWwindow *window, const float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    } else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        TextureVal += 0.01;
        TextureVal = MathUtils::Clamp(TextureVal, 0.f, 1.f);
    } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        TextureVal -= 0.01;
        TextureVal = MathUtils::Clamp(TextureVal, 0.f, 1.f);
    }

    const auto camForward = camRot.ToVec3();
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camPos += camSpeed * camForward * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camPos -= camSpeed * camForward * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camPos += camSpeed * glm::normalize(glm::cross(camForward, camUp)) * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camPos += camSpeed * glm::normalize(glm::cross(camUp, camForward)) * deltaTime;
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *) (sizeof(float) * 3));
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

    unsigned int containerTextureId;
    glGenTextures(1, &containerTextureId);
    glBindTexture(GL_TEXTURE_2D, containerTextureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    auto containerTexture = LoadImage("Assets/container.jpg", &w, &h, &nrChannel);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, containerTexture);
    glGenerateMipmap(GL_TEXTURE_2D);
    FreeImage(containerTexture);

    if (window == nullptr)
    {
        return -1;
    }

    float deltaTime = 0.f;
    float prevFrameTotTime = 0.f;
    while (!glfwWindowShouldClose(window))
    {
        auto totTime = (float)glfwGetTime();
        deltaTime = totTime - prevFrameTotTime;
        prevFrameTotTime = totTime;

        ProcessInput(window, deltaTime);

        // Clear screen to grayish color
        glClearColor(.3f, .3f, .3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, containerTextureId);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, faceTextureId);
        shader.use();
        shader.setUniformI("ourTexture", 0);
        shader.setUniformI("ourTexture2", 1);
        shader.setUniformF("Val", TextureVal);

        // Cam
        glm::mat4 viewTf = glm::lookAt(
                camPos,
                camPos + camRot.ToVec3(),
                camUp
        );

        glm::mat4 projectionTf = glm::perspective(glm::radians(45.f), 800.f / 600.f, 0.1f, 100.f);

        auto viewTransformLoc = glGetUniformLocation(shader.GetId(), "ViewTransform");
        glUniformMatrix4fv(viewTransformLoc, 1, GL_FALSE, glm::value_ptr(viewTf));

        auto projTransformLoc = glGetUniformLocation(shader.GetId(), "ProjectionTransform");
        glUniformMatrix4fv(projTransformLoc, 1, GL_FALSE, glm::value_ptr(projectionTf));

        glBindVertexArray(VAO);
        for (auto vec: cubePositions)
        {
            glm::mat4 transform(1.0f);
            transform = glm::translate(transform, vec);
            transform = glm::rotate(
                    transform,
                    glm::radians(20.f) * (float) glfwGetTime(),
                    glm::vec3(1.f, 0.5f, 0.0f)
            );

            auto transformLoc = glGetUniformLocation(shader.GetId(), "Transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
