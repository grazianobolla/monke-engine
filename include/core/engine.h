#pragma once
#include "core/display.h"
#include "core/input.h"
#include "core/sprite_renderer.h"

#include <vector>

namespace mk
{
    class Engine
    {
    private:
        void initialize();

    public:
        mk::Display display;
        mk::Input input;
        mk::SpriteRenderer sprite_renderer;

        Engine(){};
        void run(int width, int height, const char *title);
        void compute_logic(float delta);
        void compute_rendering();

        virtual void start() = 0;
        virtual void update(float delta) = 0;
        virtual void render() = 0;
    };
} // namespace mk