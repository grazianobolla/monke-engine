#pragma once
#include "texture.h"
#include "types.h"

namespace mk
{
    class Sprite
    {
    public:
        mk::Rect texture_rect;
        mk::Texture *texture_ptr;

        bool loaded = false;

        Sprite() {}
        Sprite(const char *texture_resource_name, mk::Rect tex_rect = {-1, -1, -1, -1});
        void load(const char *texture_resource_name, mk::Rect tex_rect = {-1, -1, -1, -1});
    };
};