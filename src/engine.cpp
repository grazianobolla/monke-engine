#include "engine.h"
#include "resource_loader.h"

std::vector<mk::Tickable *> mk::Engine::tickable_elements;

void mk::Engine::run(int width, int height, const char *title)
{
    this->display.create(width, height, title);
    this->input.set(this->display.window);

    this->initialize();

    this->start();
    double now = 0, last_time = 0;
    float delta = 0;

    while (glfwWindowShouldClose(display.window) == false)
    {
        now = glfwGetTime();
        delta = now - last_time;
        last_time = now;

        //update tickable elements
        for (mk::Tickable *e : this->tickable_elements)
            e->update();

        glClear(GL_COLOR_BUFFER_BIT);

        this->update(delta);

        glfwSwapBuffers(display.window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void mk::Engine::add_tickable_element(mk::Tickable *element)
{
    tickable_elements.push_back(element);
    log_info("added new tickable element");
}

void mk::Engine::initialize()
{
    mk::ResourceLoader::load_shader("shaders/vertex.glsl", "shaders/fragment.glsl", "default_shader");
    log_info("initialized engine");
}