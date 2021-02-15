#include "display.h"

void mk::Display::create(int w, int h, const char *t, int gl_major, int gl_minor)
{
    //save data
    this->width = w;
    this->height = h;
    this->title = t;
    this->opengl_major = gl_major;
    this->opengl_minor = gl_minor;

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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void mk::Display::framebuffer_resize_cb(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}