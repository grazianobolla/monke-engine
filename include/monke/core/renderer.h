#pragma once
#include "monke/core/batch_renderer.h"
#include "monke/core/sprite_renderer.h"

namespace mk
{
    class Renderer
    {
    public:
        void initialize();
        void draw(mk::Texture *texture, mk::Rectf texture_rect, mk::Vector2 position, mk::Vector2 scale);
        void draw(const mk::Sprite &sprite);
        void flush();

    private:
        mk::BatchRenderer batch_renderer;
        mk::SpriteRenderer sprite_renderer;
    };
}