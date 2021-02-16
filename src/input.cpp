#include "input.h"

int mk::Input::key_states[GLFW_KEY_LAST];
glm::vec2 mk::Input::mouse_position;

void mk::Input::set(GLFWwindow *window)
{
    glfwSetKeyCallback(window, this->key_input_callback);
    glfwSetCursorPosCallback(window, this->cursor_position_callback);

    //initialize key array
    for (int i = 0; i < GLFW_KEY_LAST; i++)
        this->key_states[i] = 0;
}

void mk::Input::key_input_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    key_states[key] = action;
}

void mk::Input::cursor_position_callback(GLFWwindow *window, double x, double y)
{
    mouse_position = {x, y};
}
