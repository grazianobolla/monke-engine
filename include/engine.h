#pragma once
#include "display.h"
#include "input.h"

namespace mk
{
    class Engine
    {
    public:
        mk::Display display;
        mk::Input input;

        Engine(){};
        void run(int width, int height, const char *title);
        virtual void start() = 0;
        virtual void update(float delta) = 0;
    };
} // namespace mk