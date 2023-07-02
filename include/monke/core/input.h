#pragma once
#include "monke/core/types.h"

#include <GLFW/glfw3.h>

namespace mk
{
    struct InputEvent
    {
        int type, code, action;
    };

    class Input
    {
    public:
        enum Type
        {
            KEYBOARD,
            MOUSE
        };

        enum KeyGroup
        {
            WASD_KEYS,
            ARROW_KEYS
        };

        GLFWwindow *window;

        Input() {}

        // Installs the input callbacks on the passed window.
        void install_callbacks(GLFWwindow *);

        // Returns mouse position relative to the screen.
        mk::Vector2 get_mouse_pos();

        // Returns normalized direction vector for WASD/ARROW keys.
        mk::Vector2 get_direction(KeyGroup group);

    private:
        static void key_input_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
        static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    };
} // namespace mk