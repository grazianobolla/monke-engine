#include "sprite.h"
#include "resource_loader.h"

mk::Sprite::Sprite(const char *texture_resource_name, mk::Rect tex_rect)
{
    this->load(texture_resource_name, tex_rect);
}

void mk::Sprite::load(const char *texture_resource_name, mk::Rect tex_rect)
{
    this->texture_ptr = static_cast<mk::Texture *>(mk::ResourceLoader::get(texture_resource_name));

    if (tex_rect == mk::Rect{-1, -1, -1, -1})
        this->texture_rect = {0, 0, this->texture_ptr->width, this->texture_ptr->height};
    else
        this->texture_rect = tex_rect;

    if (this->texture_ptr != nullptr && this->texture_rect != mk::Rect{-1, -1, -1, -1})
    {
        this->loaded = true;
    }
}