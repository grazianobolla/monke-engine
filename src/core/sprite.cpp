#include "monke/core/sprite.h"
#include "monke/core/resource_loader.h"
#include "monke/core/log.h"

mk::Sprite::Sprite(const char *texture_path, mk::Vector2 _position, mk::Vector2 _scale, mk::Rectf _rect)
{
    this->texture_ptr = mk::ResourceLoader::load_texture(texture_path);
    this->position = _position;
    this->scale = _scale;
    this->texture_rect = _rect;

    if (this->texture_ptr == nullptr)
    {
        log_info("null texture");
        return;
    }

    this->loaded = true;
}