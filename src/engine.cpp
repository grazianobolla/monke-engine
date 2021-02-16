#include "engine.h"

void mk::Engine::run(int width, int height, const char *title)
{
    this->display.create(width, height, title);
    this->input.set(this->display.window);

    this->start();
    double now = 0, last_time = 0;
    float delta = 0;

    while (glfwWindowShouldClose(display.window) == false)
    {
        now = glfwGetTime();
        delta = now - last_time;
        last_time = now;

        glClear(GL_COLOR_BUFFER_BIT);

        this->update(delta);

        glfwSwapBuffers(display.window);
        glfwPollEvents();
    }

    glfwTerminate();
}