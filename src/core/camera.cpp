#include "monke/core/camera.h"

glm::mat4 mk::Camera::get_matrix() const
{
    glm::mat4 m = glm::mat4(1);
    m = glm::translate(m, glm::vec3(-position.x, -position.y, 0));
    return m;
}