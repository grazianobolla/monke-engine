#include "monke/core/imgui_utils.h"
#include "monke/external/imgui/imgui.h"

static char buf[12] = "abc";

void mk::render_engine_data()
{
    static float f = 0;

    ImGui::Begin("Engine Info", NULL, ImGuiWindowFlags_None);
    ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::End();
}