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

        GLFWwindow *window;

        Input() {}

        // Installs the input callbacks on the specified window.
        void install_callbacks(GLFWwindow *);

        // Returns mouse position relative to the screen.
        mk::Vector2 get_mouse_pos();

        // Returns normalized direction vector for WASD/ARROW keys.
        mk::Vector2 get_direction();

    private:
        static mk::Vector2 input_direction; // stores the un-normalized direction vector for the movement keys
        static void calculate_input_direction(int key, int action);

        static void key_input_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
        static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    };
} // namespace mk