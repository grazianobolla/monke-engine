#include "engine.h"
#include "resource_loader.h"
#include "tickable.h"

#include <algorithm>

std::vector<mk::Tickable *> mk::Engine::tickable_elements;
mk::StateManager mk::Engine::state_manager;

void mk::Engine::run(int width, int height, const char *title)
{
    //initialize opengl
    this->display.create(width, height, title);
    this->initialize();

    //initialize input
    this->input.set(this->display.window);
    //initialize renderer
    this->renderer.initialize();

    this->start(); //virtual func
    double now = 0, last_time = 0;
    float delta = 0;

    while (glfwWindowShouldClose(display.window) == false)
    {
        now = glfwGetTime();
        delta = now - last_time;
        last_time = now;

        //logic
        for (mk::Tickable *e : this->tickable_elements)
            e->update();

        glfwPollEvents();

        this->update(delta);

        //rendering
        glClear(GL_COLOR_BUFFER_BIT);
        this->render();
        this->renderer.flush();
        glfwSwapBuffers(display.window);
    }

    glfwTerminate();
}

void mk::Engine::add_tickable_element(mk::Tickable *element)
{
    tickable_elements.push_back(element);
    log_info("added new tickable element");
}

void mk::Engine::remove_tickable_element(mk::Tickable *element)
{
    auto found_element = std::find(tickable_elements.begin(), tickable_elements.end(), element);
    if (found_element != std::end(tickable_elements))
        tickable_elements.erase(found_element);

    log_info("deleted tickable element");
}

void mk::Engine::initialize()
{
    mk::ResourceLoader::load_shader("shaders/vertex.glsl", "shaders/fragment.glsl", "default_shader");
}