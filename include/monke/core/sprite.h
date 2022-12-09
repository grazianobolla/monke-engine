#pragma once
#include "monke/core/texture.h"
#include "monke/core/types.h"

namespace mk
{
    class Sprite
    {
    public:
        mk::Texture *texture_ptr;
        mk::Rectf texture_rect;
        mk::Vector2 position, scale;

        bool loaded = false;

        Sprite() {}
        Sprite(const char *texture_path, mk::Vector2 position = {0, 0}, mk::Vector2 scale = {0, 0}, mk::Rectf texture_rect = {0, 0, 0, 0});
    };
};