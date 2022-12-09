#include "monke/core/engine.h"
#include "monke/core/input.h"
#include "monke/core/log.h"

void mk::Input::set(GLFWwindow *win)
{
    this->window = win;
    glfwSetKeyCallback(window, this->key_input_callback);
    glfwSetMouseButtonCallback(window, this->mouse_button_callback);
}

void mk::Input::key_input_callback(GLFWwindow *window, int key, int code, int action, int mods)
{
    mk::Engine *engine = reinterpret_cast<mk::Engine *>(glfwGetWindowUserPointer(window));
    engine->input_event(TYPE::KEYBOARD, code, action);
}

void mk::Input::mouse_button_callback(GLFWwindow *window, int code, int action, int mods)
{
    mk::Engine *engine = reinterpret_cast<mk::Engine *>(glfwGetWindowUserPointer(window));
    engine->input_event(TYPE::MOUSE, code, action);
}

mk::Vector2 mk::Input::get_mouse_pos()
{
    double x, y;
    glfwGetCursorPos(this->window, &x, &y);
    return {x, y};
}