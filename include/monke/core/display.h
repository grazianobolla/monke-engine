#pragma once
#include "monke/core/log.h"
#include "monke/core/types.h"

#include "monke/external/glm/glm.hpp"
#include "monke/external/glad/glad.h"

#include "monke/external/imgui/imgui.h"

#include <GLFW/glfw3.h>
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
        mk::Vector2 get_size();
        void clear_buffer_color();
        void swap_buffer();
        void cleanup();

    private:
        int width, height;
        int opengl_major, opengl_minor;
        std::string title;

        static void framebuffer_resize_cb(GLFWwindow *window, int width, int height);
        const char *get_glsl_version();
    };
} // namespace mk