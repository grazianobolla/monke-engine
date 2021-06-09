#pragma once
#include "types.h"

namespace mk
{
    struct Collider
    {
    public:
        Collider(const mk::Rect &);
        bool CollidingWith(const mk::Rect &);

    private:
        mk::Rect collision_shape;
    };
}