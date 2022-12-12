#include "monke/core/sprite.h"
#include "monke/core/resource_loader.h"
#include "monke/core/log.h"

void mk::Sprite::load(const char *texture_path, mk::Vector2 _position, float _angle, mk::Vector2 _scale, mk::Rectf _rect)
{
    this->texture_ptr = mk::ResourceLoader::load_texture(texture_path);
    this->position = _position;
    this->scale = _scale;
    this->angle = _angle;

    if (this->texture_ptr == nullptr)
    {
        log_info("null texture");
        return;
    }

    if (_rect == mk::Rectf{0, 0, 0, 0})
    {
        this->texture_rect = {0, 0, this->texture_ptr->width, this->texture_ptr->height};
    }
    else
    {
        this->texture_rect = _rect;
    }

    this->loaded = true;
}