#include "engine.h"

void mk::Engine::run(int width, int height, const char *title)
{
    this->display.create(width, height, title);

    this->start();
    while (glfwWindowShouldClose(display.window) == false)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        this->update();

        glfwSwapBuffers(display.window);
        glfwPollEvents();
    }

    glfwTerminate();
}