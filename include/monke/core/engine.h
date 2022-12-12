#pragma once
#include "monke/core/display.h"
#include "monke/core/input.h"
#include "monke/core/renderer.h"

#include <vector>

namespace mk
{
    class Engine
    {
    public:
        mk::Display display;
        mk::Input input;

        Engine(){};
        void run(int width, int height, const char *title);
        void compute_logic(float delta);
        void compute_rendering();

        virtual void start() = 0;
        virtual void on_input(mk::InputEvent event) = 0;
        virtual void update(float delta) = 0;
        virtual void render(mk::Renderer *batch) = 0;

    private:
        void initialize();
        mk::Renderer renderer;
    };
} // namespace mk