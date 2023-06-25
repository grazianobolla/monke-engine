#include "monke/core/engine.h"
#include "monke/core/resource_loader.h"

#include "monke/external/imgui/imgui.h"
#include "monke/external/imgui/imgui_impl_glfw.h"
#include "monke/external/imgui/imgui_impl_opengl3.h"

#include <thread>

void mk::Engine::run(int width, int height, const char *title)
{
    // creates windows obj
    this->display.create(width, height, title);

    // loads resources like shaders/textures
    this->initialize();

    // sets user pointer to this (engine object)
    glfwSetWindowUserPointer(this->display.window, this);

    this->input.set(this->display.window);

    // initialize renderer
    this->renderer.initialize();

    this->start(); // virtual function

    double now = 0, last_time = 0;
    float delta = 0;

    while (glfwWindowShouldClose(display.window) == false)
    {
        now = glfwGetTime();
        delta = now - last_time;
        last_time = now;

        glfwPollEvents();

        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        this->compute_logic(delta);
        this->compute_rendering();

        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // TODO: handle this
    }

    this->on_terminate();
}

void mk::Engine::compute_logic(float delta)
{
    this->update(delta); // virtual function
}

void mk::Engine::compute_rendering()
{
    this->display.clear_buffer_color();
    this->render(&this->renderer); // virtual function
    this->renderer.flush();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    this->display.swap_buffer();
}

void mk::Engine::initialize()
{
    mk::ResourceLoader::load_shader("shaders/batch/vertex.glsl", "shaders/batch/fragment.glsl", "batch_shader");
    mk::ResourceLoader::load_shader("shaders/sprite/vertex.glsl", "shaders/sprite/fragment.glsl", "sprite_shader");
}

void mk::Engine::on_terminate()
{
    log_info("engine shutdown..");
    this->display.cleanup();
    glfwTerminate();
}