#pragma once
#include "texture.h"
#include <glm/glm.hpp>

namespace mk
{
    typedef glm::vec4 TextureRect;

    class Sprite
    {
    public:
        mk::Texture *texture;
        TextureRect texture_rect;

        Sprite() {}
        void load(const char *texture_resource_name, TextureRect tex_rect = {-1, -1, -1, -1});
    };
};