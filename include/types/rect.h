#pragma once

namespace mk
{
    template <typename T>
    struct Rect
    {
        T x = 0, y = 0, w = 0, h = 0;

        Rect() {}

        template <typename P>
        Rect(P _x, P _y, P _w, P _h)
        {
            x = static_cast<T>(_x);
            y = static_cast<T>(_y);
            w = static_cast<T>(_w);
            h = static_cast<T>(_h);
        }

        //operators
        bool operator==(const Rect &rect)
        {
            if (this->x == rect.x && this->y == rect.y &&
                this->w == rect.w && this->h == rect.h)
                return true;

            return false;
        }

        bool operator!=(const Rect &rect) const
        {
            if (static_cast<Rect>(*this) == rect)
                return false;

            return true;
        }
    };

    typedef Rect<float> Rectf;
} //namespace mk