#include "monke/core/engine.h"
#include "monke/core/resource_loader.h"

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
    this->sprite_renderer.initialize();

    this->start(); // virtual function

    double now = 0, last_time = 0;
    float delta = 0;

    while (glfwWindowShouldClose(display.window) == false)
    {
        now = glfwGetTime();
        delta = now - last_time;
        last_time = now;

        this->compute_logic(delta);
        this->compute_rendering();

        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // TODO: handle this
    }

    glfwTerminate();
}

void mk::Engine::compute_logic(float delta)
{
    glfwPollEvents();
    this->update(delta); // virtual function
}

void mk::Engine::compute_rendering()
{
    this->display.clear_buffer();
    this->render(); // virtual function

    this->sprite_renderer.flush();
    // other flushes here..

    this->display.swap_buffer();
}

void mk::Engine::initialize()
{
    mk::ResourceLoader::load_shader("shaders/vertex.glsl", "shaders/fragment.glsl", "default_shader");
}