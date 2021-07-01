#include "core/collider.h"

mk::Collider::Collider(const mk::Rectf &rect)
{
    this->collision_shape = rect;
}

bool mk::Collider::CollidingWith(const mk::Rectf &rect)
{
    return false;
}