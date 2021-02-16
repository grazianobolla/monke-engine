#pragma once
#include "display.h"

namespace mk
{
    class Engine
    {
    public:
        mk::Display display;

        Engine(){};
        void run(int width, int height, const char *title);
        virtual void start() = 0;
        virtual void update() = 0;
    };
} // namespace mk