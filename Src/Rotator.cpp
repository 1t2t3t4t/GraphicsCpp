//
// Created by bossb on 19/06/2022.
//

#include "Rotator.h"

#include <glm/glm.hpp>

glm::vec3 Rotator::Direction() const
{
    const auto x = glm::cos(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
    const auto y = glm::sin(glm::radians(Pitch));
    const auto z = glm::sin(glm::radians(Yaw));
    glm::vec3 result(x, y, z);
    return glm::normalize(result);
}
