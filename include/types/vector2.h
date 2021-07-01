#pragma once
#include <math.h>

namespace mk
{
    template <typename T>
    struct Vector2
    {
        T x = 0, y = 0;

        Vector2() {}
        template <typename P>

        Vector2(P _x, P _y)
        {
            this->x = static_cast<T>(_x);
            this->y = static_cast<T>(_y);
        }

        void Normalize()
        {
            float magnitude = std::sqrt(this->x * this->x + this->y * this->y);
            if (magnitude > 0)
            {
                this->x /= magnitude;
                this->y /= magnitude;
            }
        }
    };

    typedef mk::Vector2<float> Vector2f;
    typedef mk::Vector2<int> Vector2i;
} //namespace mk
