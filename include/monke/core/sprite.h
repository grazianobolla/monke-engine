#pragma once
#include "monke/core/texture.h"
#include "monke/core/types.h"

namespace mk
{
    class Sprite
    {
    public:
        mk::Rectf texture_rect;
        mk::Texture *texture;

        mk::Vector2 position, scale;
        float rotation = 0;

        bool loaded = false;

        Sprite() {}
        void load(const char *texture_path, mk::Vector2 position = {0, 0}, float rotation = 0, mk::Vector2 scale = {1, 1}, mk::Rectf texture_rect = {0, 0, 0, 0});
    };
};