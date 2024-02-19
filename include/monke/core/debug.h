#pragma once
#include "monke/core/engine.h"
#define DELTA_SAMPLES 128

namespace mk
{
    // Debug class, used to render information about the engine.
    class Debug
    {
    public:
        void initialize(Engine *engine);

        // To be called on the update() function, collects data.
        void update(float delta);

        // To be called on the render() function, displays engine debug information.
        void render_debug_data();

    private:
        Engine *engine;
        float delta_history[DELTA_SAMPLES]; // stores the last DELTA_SAMPLES delta values in ms
        float average_delta = 0;
        int samples_recorded = 0;
        int margin = 32;      // Margin at top and bottom of the graph
        float delta_peak = 0; // Max delta value reached in the last cycle of DELTA_SAMPLES
    };
}