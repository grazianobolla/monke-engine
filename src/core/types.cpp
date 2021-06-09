#include "types.h"

#include <math.h>
mk::Vector2 mk::math::Normalize(const Vector2 &a)
{
    float magnitude = std::sqrt(a.x * a.x + a.y * a.y);
    return {a.x / magnitude, a.y / magnitude};
}