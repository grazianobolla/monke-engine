#pragma once
#include "monke/external/glm/glm.hpp"
#include "monke/external/glm/gtc/matrix_transform.hpp"

#include "monke/types/vector2.h"

namespace mk
{
    class Camera
    {
    public:
        mk::Vector2 position;

        glm::mat4 get_matrix() const
        {
            glm::mat4 m = glm::mat4(1);
            m = glm::translate(m, glm::vec3(-position.x, -position.y, 0));
            return m;
        }
    };
}