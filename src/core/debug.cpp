#include "monke/core/debug.h"

#include "monke/core/imgui_helper.h"

void mk::Debug::update(float delta)
{
    // Push-back latest delta into the array
    for (int i = 0; i < DELTA_SAMPLES - 1; i++)
        delta_history[i] = delta_history[i + 1]; // Move all elements backwards once

    delta_history[DELTA_SAMPLES - 1] = delta * 1000; // Fill last index with new value

    samples_recorded++;

    // Calculate average delta every 128 records (1 cycle)
    if (samples_recorded >= DELTA_SAMPLES)
    {
        average_delta = 0;
        delta_peak = 0;

        float count = 0;
        for (int i = 0; i < DELTA_SAMPLES; i++)
        {
            float sample = delta_history[i];
            count += sample;

            if (delta_history[i] > delta_peak)
                delta_peak = sample;
        }

        average_delta = count / DELTA_SAMPLES;
        samples_recorded = 0;
    }
}

void mk::Debug::render_debug_data()
{
    ImGui::Begin("Engine Info", NULL, ImGuiWindowFlags_None);
    ImGui::Text("Framerate: %.1f", mk::ImGUIHelper::imgui_io->Framerate);

    // Frametime graph
    float min = average_delta - margin;
    float max = delta_peak + margin;
    ImGui::PlotLines("Frametime", this->delta_history, DELTA_SAMPLES, 0, NULL, min, max, ImVec2(0, 40.0f));

    mk::ImGUIHelper::textVector2("Input Direction:\t(%.1f, %.1f)", engine->input.get_direction());
    mk::ImGUIHelper::textVector2("Camera Position:\t(%.1f, %.1f)", engine->camera.position);
    mk::ImGUIHelper::textVector2("Mouse Position: \t(%.0f, %.0f)", engine->input.get_mouse_pos());

    ImGui::End();
}

void mk::Debug::initialize(Engine *engine)
{
    this->engine = engine;
    log_info("Debug class initialized with engine pointer");
}