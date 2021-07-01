#include "core/input.h"
#include "core/log.h"

int mk::Input::key_states[GLFW_KEY_LAST];
int mk::Input::mouse_button[GLFW_MOUSE_BUTTON_LAST];

void mk::Input::set(GLFWwindow *win)
{
    this->window = win;
    glfwSetKeyCallback(window, this->key_input_callback);
    glfwSetMouseButtonCallback(window, this->mouse_button_callback);

    //initialize key array
    for (int i = 0; i < GLFW_KEY_LAST; i++)
        this->key_states[i] = KEY_STATE::NONE;
}

void mk::Input::key_input_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    key_states[key] = action > 0 ? KEY_STATE::PRESSED : KEY_STATE::NONE;
}

void mk::Input::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    mouse_button[button] = action > 0 ? KEY_STATE::PRESSED : KEY_STATE::NONE;
}

mk::Vector2i mk::Input::get_mouse_pos()
{
    double x, y;
    glfwGetCursorPos(this->window, &x, &y);
    return {x, y};
}