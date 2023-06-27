#include "monke/core/engine.h"
#include "monke/core/resource_loader.h"

#include "monke/core/imgui_helper.h"

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
    double delta = 0;

    while (glfwWindowShouldClose(display.window) == false)
    {
        now = glfwGetTime();
        delta = now - last_time;
        last_time = now;

        glfwPollEvents();

        mk::ImGUIHelper::new_frame();

        float f_delta = static_cast<float>(delta);
        this->compute_logic(f_delta);
        this->compute_rendering();

        // std::this_thread::sleep_for(std::chrono::milliseconds(1)); // TODO: handle this
    }

    this->on_terminate();
}

void mk::Engine::compute_logic(float delta)
{
    this->update(delta); // virtual function
}

void mk::Engine::compute_rendering()
{
    this->renderer.update_shader(this->display.projection_matrix, this->camera.get_matrix());
    this->display.clear_buffer_color();

    this->render(&this->renderer); // virtual function
    this->renderer.flush();
    mk::ImGUIHelper::render();

    this->display.swap_buffer();
}

void mk::Engine::initialize()
{
    mk::ResourceLoader::load_shader("shaders/vertex.glsl", "shaders/fragment.glsl", "default_shader"); // load shaders
    this->camera = mk::Camera();                                                                       // create camera
}

void mk::Engine::on_terminate()
{
    log_info("engine shutdown..");
    this->display.cleanup();
    glfwTerminate();
}