#include "input.h"

int mk::Input::key_states[GLFW_KEY_LAST];
mk::Vector2 mk::Input::mouse_position;
int mk::Input::mouse_button[GLFW_MOUSE_BUTTON_LAST];

void mk::Input::set(GLFWwindow *window)
{
    glfwSetKeyCallback(window, this->key_input_callback);
    glfwSetCursorPosCallback(window, this->cursor_position_callback);
    glfwSetMouseButtonCallback(window, this->mouse_button_callback);

    //initialize key array
    for (int i = 0; i < GLFW_KEY_LAST; i++)
        this->key_states[i] = KEY_STATE::NONE;
}

void mk::Input::key_input_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    key_states[key] = action > 0 ? KEY_STATE::PRESSED : KEY_STATE::NONE;
}

void mk::Input::cursor_position_callback(GLFWwindow *window, double x, double y)
{
    mouse_position = {x, y};
}

void mk::Input::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    mouse_button[button] = action > 0 ? KEY_STATE::PRESSED : KEY_STATE::NONE;
}
