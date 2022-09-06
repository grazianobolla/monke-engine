#include "core/sprite.h"
#include "core/resource_loader.h"
#include "core/log.h"

mk::Sprite::Sprite(const char *texture_path, mk::Rectf tex_rect)
{
    this->load(texture_path, tex_rect);
}

void mk::Sprite::load(const char *path, mk::Rectf tex_rect)
{
    this->texture_ptr = mk::ResourceLoader::load_texture(path);

    if (this->texture_ptr == nullptr)
    {
        log_info("null texture");
        return;
    }

    if (tex_rect == mk::Rectf{-1, -1, -1, -1})
        this->texture_rect = {0, 0, this->texture_ptr->width, this->texture_ptr->height};
    else
        this->texture_rect = tex_rect;

    // check if the sprite is loaded
    if (this->texture_ptr != nullptr && this->texture_rect != mk::Rectf{-1, -1, -1, -1})
    {
        this->loaded = true;
    }
}