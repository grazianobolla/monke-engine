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
        void draw(const glm::vec2 &position, const glm::vec2 &scale = {1, 1});
        void draw_partial(const glm::vec2 &position, const glm::vec4 &texture_coordinates, const glm::vec2 &scale = {1, 1});
        void set_tint(const glm::vec4 &tint);

    private:
        unsigned int sprite_vao_id = 0, uv_array_buffer = 0;

        //pointers to shader and texture data, necessary to
        //render the sprite, can be shared among Sprites
        Shader *shader;
        Texture *texture;

        void setup_sprite_vertex_data();
    };
} // namespace mk