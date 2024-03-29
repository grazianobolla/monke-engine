// Dear ImGUI implementation helper
#pragma once
#include <GLFW/glfw3.h>
#include "monke/external/imgui/imgui.h"
#include "monke/types/vector2.h"

namespace mk
{
    class ImGUIHelper
    {
    public:
        static void initialize_context(GLFWwindow *window, const char *glsl_version);
        static void cleanup();
        static void new_frame();
        static void render();

        static bool add_mouse_event(int button, bool pressed);
        static bool add_keyboard_event(int button, bool pressed);
        static void add_scroll_event(double x, double y);

        static ImGuiKey key_from_glfw(int glfw_code);

        static void textVector2(const char *fmt, mk::Vector2 v);

        static ImGuiIO *imgui_io;
    };
}