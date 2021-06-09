#include "collider.h"

mk::Collider::Collider(const mk::Rect &rect)
{
    this->collision_shape = rect;
}

bool mk::Collider::CollidingWith(const mk::Rect &rect)
{
    return false;
}