#pragma once
#include "types.h"

#include <glad/glad.h>

namespace mk
{
    class Shader
    {
    public:
        unsigned int id = 0;

        Shader() {}
        bool load(const char *vert_path, const char *frag_path);
        void use();
        void set_mat4(const char *uniform_name, const mk::Mat4 &matrix);
        void set_vec4(const char *uniform_name, const mk::Vector4 &vector);
        void set_vec2(const char *uniform_name, const mk::Vector2 &vector);

    private:
        unsigned int create_shader(const char *path, unsigned int type);
        unsigned int get_uniform_location(const char *uniform_name);
    };
} // namespace mk