#pragma once
#include "engine.h"

namespace mk
{
    class Tickable
    {
    public:
        virtual void update() = 0;

        ~Tickable()
        {
            mk::Engine::remove_tickable_element(this);
        }
    };
}