#include "monke/core/imgui_utils.h"

#include "monke/core/imgui_helper.h"
#include "monke/external/imgui/imgui.h"

void mk::render_engine_data()
{
    ImGui::Begin("Engine Info", NULL, ImGuiWindowFlags_None);
    ImGui::Text("Framerate: %.1f FPS", mk::ImGUIHelper::imgui_io->Framerate);
    ImGui::End();
}