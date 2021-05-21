#pragma once
#include "types.h"

#include <GLFW/glfw3.h>

namespace mk
{
    class Input
    {
    public:
        enum KEY_STATE
        {
            NONE,
            PRESSED
        };

        static mk::Vector2 mouse_pos;
        static int key_states[GLFW_KEY_LAST];
        static int mouse_button[GLFW_MOUSE_BUTTON_LAST];

        Input() {}
        void set(GLFWwindow *window);

    private:
        static void key_input_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
        static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
    };
} // namespace mk