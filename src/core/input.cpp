#include "monke/core/engine.h"
#include "monke/core/input.h"
#include "monke/core/log.h"

#include "monke/external/imgui/imgui.h"
#include "monke/external/imgui/imgui_impl_glfw.h"
#include "monke/external/imgui/imgui_impl_opengl3.h"

void mk::Input::set(GLFWwindow *win)
{
    this->window = win;
    glfwSetKeyCallback(window, this->key_input_callback);
    glfwSetMouseButtonCallback(window, this->mouse_button_callback);
    glfwSetScrollCallback(window, this->scroll_callback);
}

void mk::Input::key_input_callback(GLFWwindow *window, int key, int code, int action, int mods)
{
    mk::Engine *engine = static_cast<mk::Engine *>(glfwGetWindowUserPointer(window));
    engine->on_input(InputEvent{
        .type = TYPE::KEYBOARD,
        .code = key,
        .action = action});
}

void mk::Input::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    ImGuiIO &io = ImGui::GetIO();
    io.AddMouseButtonEvent(button, action == GLFW_PRESS);

    if (!io.WantCaptureMouse)
    {
        mk::Engine *engine = static_cast<mk::Engine *>(glfwGetWindowUserPointer(window));
        engine->on_input(InputEvent{
            .type = TYPE::MOUSE,
            .code = button,
            .action = action});
    }
}

void mk::Input::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    ImGuiIO &io = ImGui::GetIO();
    io.AddMouseWheelEvent(xoffset, yoffset);
}

mk::Vector2 mk::Input::get_mouse_pos()
{
    double x, y;
    glfwGetCursorPos(this->window, &x, &y);
    return {x, y};
}