#include "texture.h"
#include "log.h"
#include "engine.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

bool mk::Texture::load(const char *path)
{
    //stbi_set_flip_vertically_on_load(false); //for some reason opengl loads images backwards

    unsigned char *image_data = stbi_load(path, &this->width, &this->height, &this->channels, 0);
    if (image_data == NULL)
    {
        log_info("failed to load texture " << path);
        stbi_image_free(image_data);
        return false;
    }

    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);

    //set texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image_data);

    glBindTexture(GL_TEXTURE_2D, 0);

    log_info("loaded texture " << path << " (" << this << ")"
                               << " id:" << this->id);
    return true;
}

void mk::Texture::use()
{
    //we dont call glBindTexture if the current texture is the same, this way we save some resources
    if (mk::Engine::state_manager.current_texture != this && this != nullptr)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->id);
        mk::Engine::state_manager.current_texture = this;
        fst("binded texture");
    }
}