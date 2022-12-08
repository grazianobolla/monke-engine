#include "monke/core/input.h"
#include "monke/core/log.h"

int mk::Input::keyboard_states[GLFW_KEY_LAST];
int mk::Input::mouse_states[GLFW_MOUSE_BUTTON_LAST];

void mk::Input::set(GLFWwindow *win)
{
    this->window = win;
    glfwSetKeyCallback(window, this->key_input_callback);
    glfwSetMouseButtonCallback(window, this->mouse_button_callback);
}

void mk::Input::key_input_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    keyboard_states[key] = action > 0 ? KEY_STATE::PRESSED : KEY_STATE::NONE;
}

void mk::Input::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    mouse_states[button] = action > 0 ? KEY_STATE::PRESSED : KEY_STATE::NONE;
}

mk::Vector2 mk::Input::get_mouse_pos()
{
    double x, y;
    glfwGetCursorPos(this->window, &x, &y);
    return {x, y};
}

bool mk::Input::is_key_pressed(int code)
{
    if (code > GLFW_KEY_LAST || code < 0)
        return false;

    return keyboard_states[code] == KEY_STATE::PRESSED;
}

bool mk::Input::is_mouse_pressed(int code)
{
    if (code > GLFW_MOUSE_BUTTON_LAST || code < 0)
        return false;

    return mouse_states[code] == KEY_STATE::PRESSED;
}