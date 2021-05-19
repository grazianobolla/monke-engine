#include "sprite.h"
#include "resource_loader.h"

void mk::Sprite::load(const char *texture_resource_name, TextureRect tex_rect)
{
    this->texture = static_cast<mk::Texture *>(mk::ResourceLoader::get(texture_resource_name));
    this->texture_rect = tex_rect;
}