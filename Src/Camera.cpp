//
// Created by bossb on 19/06/2022.
//

#include <glm/ext/matrix_transform.hpp>
#include "Camera.h"

const Rotator &Camera::getRot() const
{
    return Rot;
}

void Camera::setRot(const Rotator &rot)
{
    Rot = rot;
}

const glm::vec3 &Camera::getPos() const
{
    return Pos;
}

void Camera::setPos(const glm::vec3 &pos)
{
    Pos = pos;
}

const glm::vec3 &Camera::getUp() const
{
    return Up;
}

glm::mat4 Camera::ViewTransform() const
{
    glm::vec3 zaxis = -Rot.Direction();
    glm::vec3 xaxis = glm::normalize(glm::cross(WorldUp, zaxis));
    glm::vec3 yaxis = glm::normalize(glm::cross(zaxis, xaxis));
    glm::mat4 rotTransform(1.0f);
    // Right
    rotTransform[0][0] = xaxis.x;
    rotTransform[1][0] = xaxis.y;
    rotTransform[2][0] = xaxis.z;

    // Up
    rotTransform[0][1] = yaxis.x;
    rotTransform[1][1] = yaxis.y;
    rotTransform[2][1] = yaxis.z;

    // Dir
    rotTransform[0][2] = zaxis.x;
    rotTransform[1][2] = zaxis.y;
    rotTransform[2][2] = zaxis.z;
    glm::mat4 iMatrix(1.0f);
    return rotTransform * glm::translate(iMatrix, -Pos);
}
