#include "engine.h"
#include "resource_loader.h"

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