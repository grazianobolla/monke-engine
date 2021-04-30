#pragma once
#include "opengl_object.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace mk
{
    class Shader : public mk::OpenGLObject
    {
    public:
        Shader() {}
        bool load(const char *vert_path, const char *frag_path);
        void use();
        void set_mat4(const char *uniform_name, const glm::mat4 &matrix);
        void set_vec4(const char *uniform_name, const glm::vec4 &vector);
        void set_vec2(const char *uniform_name, const glm::vec2 &vector);

    private:
        unsigned int create_shader(const char *path, unsigned int type);
        unsigned int get_uniform_location(const char *uniform_name);
    };
} // namespace mk