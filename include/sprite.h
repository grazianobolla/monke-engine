#pragma once
#include "shader.h"
#include "texture.h"
#include "opengl_object.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace mk
{
    class Sprite
    {
    public:
        bool h_inverted = false, v_inverted = false;

        Sprite() {}
        ~Sprite();

        void load(const char *texture_resource_name, const glm::vec4 &tex_coord, const char *shader_resource_name = "default_shader");
        void set_tint(const glm::vec4 &tint);
        void draw(const glm::vec2 &position, const glm::vec2 &scale = {1, 1});
        void update_rect(const glm::vec4 &tex_coord);

    protected:
        unsigned int vao_id = 0;
        unsigned int vertex_data_id = 0;
        unsigned int uv_data_id = 0;
        unsigned int ebo_id = 0;

        glm::vec4 texture_coordinates;

        //pointers to shader and texture data, necessary to
        //render the sprite, can be shared among Sprites
        Shader *shader;
        Texture *texture;

        bool loaded = false;

        void setup_sprite_vertex_data(unsigned int &vertex_array_object, unsigned int &vertex_data, unsigned int &uv_data, unsigned int &ebo, bool uv_static);
    };
} // namespace mk