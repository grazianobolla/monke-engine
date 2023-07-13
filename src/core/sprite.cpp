#include "monke/core/sprite.h"
#include "monke/core/resource_loader.h"
#include "monke/core/log.h"

void mk::Sprite::load(const char *texture_path, mk::Vector2 _position, float _rotation, mk::Vector2 _scale, mk::Rectf _rect)
{
    this->texture = mk::ResourceLoader::load_texture(texture_path);
    this->position = _position;
    this->scale = _scale;
    this->rotation = _rotation;

    if (this->texture == nullptr)
    {
        log_info("null texture");
        return;
    }

    if (_rect == mk::Rectf{0, 0, 0, 0})
    {
        this->rect = {0, 0, this->texture->width, this->texture->height};
    }
    else
    {
        this->rect = _rect;
    }

    this->loaded = true;
}