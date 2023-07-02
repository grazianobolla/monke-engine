#include "monke/core/engine.h"
#include "monke/core/input.h"
#include "monke/core/log.h"
#include "monke/core/imgui_helper.h"

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

    if (imGuiOnlyEvent == false)
    {
        mk::Engine *engine = static_cast<mk::Engine *>(glfwGetWindowUserPointer(window));
        engine->on_input(InputEvent{
            .type = Type::KEYBOARD,
            .code = key,
            .action = action});
    }
}

void mk::Input::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    bool imGuiOnlyEvent = mk::ImGUIHelper::add_mouse_event(button, action == GLFW_PRESS);

    if (imGuiOnlyEvent == false)
    {
        mk::Engine *engine = static_cast<mk::Engine *>(glfwGetWindowUserPointer(window));
        engine->on_input(InputEvent{
            .type = Type::MOUSE,
            .code = button,
            .action = action});
    }
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

mk::Vector2 mk::Input::get_direction(KeyGroup group)
{
    mk::Vector2 dir = {0, 0};
    bool arrow_keys = group == KeyGroup::ARROW_KEYS;

    int up_key = arrow_keys ? GLFW_KEY_UP : GLFW_KEY_W;
    int down_key = arrow_keys ? GLFW_KEY_DOWN : GLFW_KEY_S;
    int left_key = arrow_keys ? GLFW_KEY_LEFT : GLFW_KEY_A;
    int right_key = arrow_keys ? GLFW_KEY_RIGHT : GLFW_KEY_D;

    if (glfwGetKey(this->window, up_key) == GLFW_PRESS)
        dir.y -= 1;

    if (glfwGetKey(this->window, down_key) == GLFW_PRESS)
        dir.y += 1;

    if (glfwGetKey(this->window, left_key) == GLFW_PRESS)
        dir.x -= 1;

    if (glfwGetKey(this->window, right_key) == GLFW_PRESS)
        dir.x += 1;

    return dir.normalized();
}