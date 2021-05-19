#pragma once
#include "display.h"
#include "input.h"
#include "state_manager.h"

#include <vector>

namespace mk
{
    class Tickable;

    class Engine
    {
    private:
        static std::vector<mk::Tickable *> tickable_elements;

        void initialize();

    public:
        static mk::StateManager state_manager;
        mk::Display display;
        mk::Input input;

        static void *last_texture;

        Engine(){};
        void run(int width, int height, const char *title);
        virtual void start() = 0;
        virtual void update(float delta) = 0;
        virtual void render() = 0;

        static void add_tickable_element(mk::Tickable *element);
        static void remove_tickable_element(mk::Tickable *element);
    };
} // namespace mk