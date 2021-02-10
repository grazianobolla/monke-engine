#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace mk
{
    class Shader
    {
    public:
        Shader() {}
        bool load(const char *vert_path, const char *frag_path);
        void use();
        void set_mat4(const char *uniform_name, const glm::mat4 &matrix);
        unsigned int get();

    private:
        unsigned int id;
        unsigned int create_shader(const char *path, unsigned int type);
        unsigned int get_uniform_location(const char *uniform_name);
    };
} // namespace mk