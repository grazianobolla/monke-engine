#include "monke/core/renderer.h"

void mk::Renderer::initialize()
{
    this->batch_renderer.initialize();
    this->sprite_renderer.initialize();
}

void mk::Renderer::draw(mk::Texture *texture, mk::Rectf texture_rect, mk::Vector2 position, mk::Vector2 scale)
{
    this->batch_renderer.draw(texture, texture_rect, position, scale);
}

void mk::Renderer::draw(const mk::Sprite &sprite)
{
    this->sprite_renderer.draw(sprite);
}

void mk::Renderer::flush()
{
    this->batch_renderer.flush();
    // other flushes here
}