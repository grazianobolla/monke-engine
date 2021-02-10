#pragma once
#include "shader.h"
#include "texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace mk
{
    class Sprite
    {
    public:
        Sprite() {}
        void load(Texture *texture, Shader *shader, glm::mat4 projection);
        void draw(glm::vec2 position, glm::vec2 scale = {1, 1});

    private:
        unsigned int vao_id;

        //pointers to shader and texture data, necessary to
        //render the sprite, can be shared among Sprites
        Shader *shader;
        Texture *texture;

        void setup_vertex_data();
    };
} // namespace mk