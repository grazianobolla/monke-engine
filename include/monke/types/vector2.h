#pragma once
#include <math.h>
#include <string>

namespace mk
{
    struct Vector2
    {
        float x = 0, y = 0;

        Vector2() {}

        template <typename P>
        Vector2(P _x, P _y)
        {
            x = static_cast<float>(_x);
            y = static_cast<float>(_y);
        }

        Vector2 operator+(const Vector2 &other)
        {
            return Vector2(x + other.x, y + other.y);
        }

        void operator+=(const Vector2 &other)
        {
            x += other.x;
            y += other.y;
        }

        Vector2 operator-(const Vector2 &other)
        {
            return Vector2(x - other.x, y - other.y);
        }

        void operator-=(const Vector2 &other)
        {
            x -= other.x;
            y -= other.y;
        }

        Vector2 operator*(const Vector2 &other)
        {
            return Vector2(x * other.x, y * other.y);
        }

        void operator*=(const Vector2 &other)
        {
            x *= other.x;
            y *= other.y;
        }

        Vector2 operator-()
        {
            return Vector2(-x, -y);
        }

        template <typename P>
        Vector2 operator*(const P &other)
        {
            return Vector2(x * other, y * other);
        }

        std::string to_string()
        {
            return "(" + std::to_string(x) + " " + std::to_string(y) + ")";
        }

        void normalize()
        {
            float magnitude = std::sqrt(x * x + y * y);

            if (magnitude > 0)
            {
                x /= magnitude;
                y /= magnitude;
            }
        }
    };
} // namespace mk
