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
        void draw(glm::vec2 position, glm::vec2 scale = {1, 1});

    private:
        //stores the id of the vao that will be used by all sprites
        static unsigned int sprite_vao_id;

        //pointers to shader and texture data, necessary to
        //render the sprite, can be shared among Sprites
        Shader *shader;
        Texture *texture;

        void setup_sprite_vertex_data();
    };
} // namespace mk