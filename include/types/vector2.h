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
            x = static_cast<T>(_x);
            y = static_cast<T>(_y);
        }

        template <typename P>
        operator Vector2<P>() const
        {
            return Vector2<P>(
                static_cast<P>(x),
                static_cast<P>(y));
        }

        void Normalize()
        {
            float magnitude = std::sqrt(x * x + y * y);

            if (magnitude > 0)
            {
                x /= magnitude;
                y /= magnitude;
            }
        }
    };

    typedef mk::Vector2<float> Vector2f;
    typedef mk::Vector2<int> Vector2i;
} //namespace mk
