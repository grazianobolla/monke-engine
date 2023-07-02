#include "monke/core/engine.h"
#include "monke/core/input.h"
#include "monke/core/log.h"
#include "monke/core/imgui_helper.h"

mk::Vector2 mk::Input::input_direction;

void mk::Input::install_callbacks(GLFWwindow *win)
{
    this->window = win;
    glfwSetKeyCallback(window, this->key_input_callback);
    glfwSetMouseButtonCallback(window, this->mouse_button_callback);
    glfwSetScrollCallback(window, this->scroll_callback);
}

void mk::Input::key_input_callback(GLFWwindow *window, int key, int code, int action, int mods)
{
    bool imGuiOnlyEvent = mk::ImGUIHelper::add_keyboard_event(key, action == GLFW_PRESS);

    if (imGuiOnlyEvent == true)
    {
        return;
    }

    calculate_input_direction(key, action);

    // propagate event to the engine
    mk::Engine *engine = static_cast<mk::Engine *>(glfwGetWindowUserPointer(window));
    engine->on_input(InputEvent{
        .type = Type::KEYBOARD,
        .code = key,
        .action = action});
}

void mk::Input::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    bool imGuiOnlyEvent = mk::ImGUIHelper::add_mouse_event(button, action == GLFW_PRESS);

    if (imGuiOnlyEvent == true)
    {
        return;
    }

    // propagate event to the engine
    mk::Engine *engine = static_cast<mk::Engine *>(glfwGetWindowUserPointer(window));
    engine->on_input(InputEvent{
        .type = Type::MOUSE,
        .code = button,
        .action = action});
}

void mk::Input::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    mk::ImGUIHelper::add_scroll_event(xoffset, yoffset);
}

mk::Vector2 mk::Input::get_mouse_pos()
{
    double x, y;
    glfwGetCursorPos(this->window, &x, &y);
    return {x, y};
}

mk::Vector2 mk::Input::get_direction()
{
    return this->input_direction.normalized();
}

void mk::Input::calculate_input_direction(int key, int action)
{
    int displacement = action == GLFW_PRESS ? 1 : -1;

    if (key == GLFW_KEY_UP || key == GLFW_KEY_W)
    {
        input_direction.y -= displacement;
    }

    if (key == GLFW_KEY_DOWN || key == GLFW_KEY_S)
    {
        input_direction.y += displacement;
    }

    if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A)
    {
        input_direction.x -= displacement;
    }

    if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D)
    {
        input_direction.x += displacement;
    }
}