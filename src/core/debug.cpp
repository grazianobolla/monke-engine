#include "monke/core/debug.h"

#include "monke/core/imgui_helper.h"

void mk::Debug::update(float delta)
{
    for (int i = 0; i < DELTA_SAMPLES - 1; i++)
        delta_history[i] = delta_history[i + 1];

    delta_history[DELTA_SAMPLES - 1] = delta * 1000;
}

void mk::Debug::render_debug_data()
{
    ImGui::Begin("Engine Info", NULL, ImGuiWindowFlags_None);
    ImGui::Text("Framerate: %.1f", mk::ImGUIHelper::imgui_io->Framerate);
    ImGui::PlotLines("Frametime", this->delta_history, DELTA_SAMPLES, 0, NULL, 14, 19, ImVec2(0, 42.0f));

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