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
        glm::mat4 get_matrix() const;
    };
}