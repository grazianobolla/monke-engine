#pragma once
#include "core/types.h"

namespace mk
{
    struct Collider
    {
    public:
        Collider(const mk::Rectf &);
        bool CollidingWith(const mk::Rectf &);

    private:
        mk::Rectf collision_shape;
    };
}