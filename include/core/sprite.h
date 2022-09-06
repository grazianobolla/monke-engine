#pragma once
#include "core/texture.h"
#include "core/types.h"

namespace mk
{
    class Sprite
    {
    public:
        mk::Rectf texture_rect;
        mk::Texture *texture_ptr;

        bool loaded = false;

        Sprite() {}
        Sprite(const char *texture_resource_name, mk::Rectf tex_rect = {-1, -1, -1, -1});
        void load(const char *path, mk::Rectf tex_rect = {-1, -1, -1, -1});
    };
};