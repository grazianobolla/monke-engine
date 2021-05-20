#include "sprite.h"
#include "resource_loader.h"

void mk::Sprite::load(const char *texture_resource_name, TextureRect tex_rect)
{
    this->texture = static_cast<mk::Texture *>(mk::ResourceLoader::get(texture_resource_name));

    if (tex_rect == TextureRect{-1, -1, -1, -1})
        this->texture_rect = {0, 0, this->texture->width, this->texture->height};
    else
        this->texture_rect = tex_rect;
}