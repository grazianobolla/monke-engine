#pragma once
#include "log.h"
#include "types.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace mk
{
    class Display
    {
    public:
        GLFWwindow *window;
        static mk::Mat4 projection;

        Display() {}
        void create(int width = 800, int height = 600, const char *title = "OpenGL Window", int opengl_major = 3, int opengl_minor = 3);
        mk::Vector2 get_size();

    private:
        int width, height;
        int opengl_major, opengl_minor;
        std::string title;

        static void framebuffer_resize_cb(GLFWwindow *window, int width, int height);
    };
} // namespace mk