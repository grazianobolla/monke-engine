#include "core/engine.h"
#include "core/resource_loader.h"

#include <thread>

void mk::Engine::run(int width, int height, const char *title)
{
    //initialize things
    this->display.create(width, height, title);
    this->initialize();
    this->input.set(this->display.window);
    this->renderer.initialize();

    this->start(); //virtual function

    double now = 0, last_time = 0;
    float delta = 0;

    while (glfwWindowShouldClose(display.window) == false)
    {
        now = glfwGetTime();
        delta = now - last_time;
        last_time = now;

        this->compute_logic(delta);
        this->compute_rendering();

        std::this_thread::sleep_for(std::chrono::milliseconds(1)); //prevents too much CPU use TODO: handle this
    }

    glfwTerminate();
}

void mk::Engine::compute_logic(float delta)
{
    glfwPollEvents();
    this->update(delta); //virtual function
}

void mk::Engine::compute_rendering()
{
    this->display.clear_buffer();
    this->render(); //virtual function
    this->renderer.flush();
    this->display.swap_buffer();
}

void mk::Engine::initialize()
{
    mk::ResourceLoader::load_shader("shaders/vertex.glsl", "shaders/fragment.glsl", "default_shader");
}