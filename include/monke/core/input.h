#pragma once
#include "monke/core/types.h"

#include <GLFW/glfw3.h>

namespace mk
{
    class Input
    {
    public:
        GLFWwindow *window;

        Input() {}
        void set(GLFWwindow *);
        mk::Vector2 get_mouse_pos();

        enum TYPE
        {
            KEYBOARD,
            MOUSE
        };

    private:
        static void key_input_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
    };
} // namespace mk