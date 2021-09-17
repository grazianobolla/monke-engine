#pragma once
#include "core/types.h"

#include <GLFW/glfw3.h>

namespace mk
{
    class Input
    {
    public:
        GLFWwindow *window;

        Input() {}
        void set(GLFWwindow *win);
        mk::Vector2i get_mouse_pos();
        bool is_key_pressed(int key_code);

    private:
        enum KEY_STATE
        {
            NONE,
            PRESSED
        };

        static int key_states[GLFW_KEY_LAST];
        static int mouse_button[GLFW_MOUSE_BUTTON_LAST];

        static void key_input_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
    };
} // namespace mk