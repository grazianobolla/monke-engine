#include "engine.h"

glm::mat4 mk::Engine::projection;

void mk::Engine::run(int width, int height, const char *title)
{
    this->display.create(width, height, title);
    this->projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);

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