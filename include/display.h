#pragma once
#include "log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

namespace mk
{
    class Display
    {
    public:
        GLFWwindow *window;
        static glm::mat4 projection;

        Display() {}
        void create(int width = 800, int height = 600, const char *title = "OpenGL Window", int opengl_major = 3, int opengl_minor = 3);

    private:
        int width, height;
        int opengl_major, opengl_minor;
        std::string title;

        static void framebuffer_resize_cb(GLFWwindow *window, int width, int height);
    };
} // namespace mk