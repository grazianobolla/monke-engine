#pragma once
#include "monke/core/display.h"
#include "monke/core/input.h"
#include "monke/core/renderer.h"
#include "monke/core/camera.h"

#include <vector>

namespace mk
{
    class Engine
    {
    public:
        mk::Display display;
        mk::Input input;
        Camera camera;

        Engine(){};
        void run(int width, int height, const char *title);
        void compute_logic(float delta);
        void compute_rendering();

        virtual void start() = 0;
        virtual void on_input(mk::InputEvent event) = 0;
        virtual void update(float delta) = 0;
        virtual void render(mk::Renderer *renderer) = 0;

    private:
        mk::Renderer renderer;

        void initialize();
        void on_terminate();
    };
} // namespace mk