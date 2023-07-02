#include "monke/core/debug.h"

#include "monke/core/imgui_helper.h"

void mk::Debug::update(float delta)
{
    for (int i = 0; i < DELTA_SAMPLES - 1; i++)
    {
        delta_history[i] = delta_history[i + 1];
    }

    delta_history[DELTA_SAMPLES - 1] = delta * 1000;
}

void mk::Debug::render_debug_data()
{
    ImGui::Begin("Engine Info", NULL, ImGuiWindowFlags_None);
    ImGui::PlotLines("Frametime", this->delta_history, DELTA_SAMPLES);
    ImGui::Text("Input Dir (%.1f, %.1f)", engine->input.get_direction(Input::WASD_KEYS).x, engine->input.get_direction(Input::WASD_KEYS).y);
    ImGui::Text("Camera Pos (%.1f, %.1f)", engine->camera.position.x, engine->camera.position.y);
    ImGui::End();
}

void mk::Debug::initialize(Engine *engine)
{
    this->engine = engine;
    log_info("Debug class initialized with engine pointer");
}