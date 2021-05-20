#include "display.h"

glm::mat4 mk::Display::projection;

void mk::Display::create(int w, int h, const char *t, int gl_major, int gl_minor)
{
    //save data
    this->width = w;
    this->height = h;
    this->title = t;
    this->opengl_major = gl_major;
    this->opengl_minor = gl_minor;

    //create projection matrix
    this->projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);

    //initialize opengl
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->opengl_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->opengl_minor);
    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);
    if (this->window == NULL)
        log_info("cant create the window");

    glfwMakeContextCurrent(this->window);

    //TODO: create a proper thing for enabling this:
    glfwSwapInterval(0);

    //sets the callback for when the window is resized
    glfwSetFramebufferSizeCallback(this->window, this->framebuffer_resize_cb);

    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false)
        log_info("cant initialize glad");

    glViewport(0, 0, this->width, this->height);

    //TODO:temp
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void mk::Display::framebuffer_resize_cb(GLFWwindow *window, int new_width, int new_height)
{
    glViewport(0, 0, new_width, new_height);
    projection = glm::ortho(0.0f, static_cast<float>(new_width), static_cast<float>(new_height), 0.0f, -1.0f, 1.0f);
}

glm::vec2 mk::Display::get_size()
{
    int w, h;
    glfwGetFramebufferSize(this->window, &w, &h);
    return {w, h};
}