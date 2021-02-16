#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace mk
{
    class Input
    {
    public:
        Input() {}
        void set(GLFWwindow *window);
        static int key_states[GLFW_KEY_LAST];
        static glm::vec2 mouse_position;

    private:
        static void key_input_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
    };
} // namespace mk