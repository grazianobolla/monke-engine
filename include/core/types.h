#pragma once
#include <glm/glm.hpp>

//rename glm types
namespace mk
{
    typedef glm::vec2 Vector2;
    typedef glm::vec4 Rect;

    namespace math
    {
        mk::Vector2 Normalize(const mk::Vector2 &);
    }
} //namespace mk