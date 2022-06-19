#pragma once

#include <glm/vec3.hpp>

class Rotator
{
public:
    float Yaw = -90.f;
    float Pitch = 0.f;
    float Roll = 0.f;

    glm::vec3 Direction() const;
};
