#pragma once

#include "Rotator.h"
#include <glm/vec3.hpp>
#include <glm/fwd.hpp>

const glm::vec3 WorldUp = {0.f, 1.f, 0.f};

class Camera
{
private:
    Rotator Rot;
    glm::vec3 Pos;
    glm::vec3 Up = WorldUp;

public:
    explicit Camera(glm::vec3 newPos) : Pos(newPos) {};

    const Rotator &getRot() const;
    void setRot(const Rotator &rot);

    const glm::vec3 &getPos() const;
    void setPos(const glm::vec3 &pos);

    const glm::vec3 &getUp() const;

    glm::mat4 ViewTransform() const;
};
