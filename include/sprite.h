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
        Sprite() {}
        void load(const char *texture_resource_name, const char *shader_resource_name);
        void set_tint(const glm::vec4 &tint);
        void draw(const glm::vec2 &position, const glm::vec2 &scale = {1, 1});
        void set_rect(const glm::vec4 &tex_coord);

    protected:
        unsigned int vao_id = 0;
        unsigned int uv_id = 0;
        glm::vec4 texture_coordinates;

        //pointers to shader and texture data, necessary to
        //render the sprite, can be shared among Sprites
        Shader *shader;
        Texture *texture;

        void setup_sprite_vertex_data(unsigned int &vertex_array_object_id, unsigned int &uv_array_object_id, bool uv_static);
    };
} // namespace mk