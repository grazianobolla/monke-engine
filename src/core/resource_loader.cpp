#include "monke/core/resource_loader.h"
#include "monke/core/log.h"

#include <string.h>

// resource map <path/key, pointer> format
std::map<const char *, mk::ResourcePointer> mk::ResourceLoader::resources;

void mk::ResourceLoader::load_shader(const char *vert_path, const char *frag_path, const char *key)
{
    if (exists(key))
    {
        log_info("shader " << key << " already exists, skipping");
        return;
    }

    mk::Shader *temp_shader = new mk::Shader();

    if (temp_shader->load(vert_path, frag_path) == false)
    {
        log_info("error while loading " << key << " shader (maybe file does not exist)");
        return;
    }

    resources.insert({key, static_cast<ResourcePointer>(temp_shader)});
    log_info("loaded shader " << vert_path << " and " << frag_path << " to key '" << key << "'");
}

mk::Texture *mk::ResourceLoader::load_texture(const char *path)
{
    // check if the texture is saved in the resource map
    if (exists(path))
    {
        log_info("texture " << path << " already exists, skipping");
        return static_cast<mk::Texture *>(resources.at(path));
    }

    mk::Texture *temp_texture = new mk::Texture();

    if (temp_texture->load(path) == false)
    {
        log_info("error while loading " << path << " texture (maybe file does not exist)");
        return nullptr;
    }

    resources.insert({path, static_cast<ResourcePointer>(temp_texture)});
    return temp_texture;
}

void mk::ResourceLoader::delete_resource(const char *resource_name, RESOURCE_TYPE resource_type)
{
    if (exists(resource_name) == true)
    {
        ResourcePointer resource_pointer = resources.at(resource_name);
        resources.erase(resource_name);

        if (resource_type == RESOURCE_TYPE::SHADER)
        {
            mk::Shader *shader = static_cast<mk::Shader *>(resource_pointer);
            glDeleteShader(shader->id);
            log_info("shader " << resource_name << " deleted");
            return;
        }

        if (resource_type == RESOURCE_TYPE::TEXTURE)
        {
            mk::Texture *texture = static_cast<mk::Texture *>(resource_pointer);
            glDeleteTextures(1, &texture->id);
            log_info("texture " << resource_name << " deleted");
            return;
        }
        return;
    }

    log_info(resource_type << resource_name << " does not exist");
}

mk::ResourcePointer mk::ResourceLoader::get(const char *resource_name)
{
    for (std::map<const char *, ResourcePointer>::iterator it = resources.begin(); it != resources.end(); ++it)
    {
        if (strcmp(resource_name, it->first) == 0)
        {
            return it->second;
        }
    }

    return nullptr;
}

bool mk::ResourceLoader::exists(const char *key)
{
    if (get(key) == nullptr)
        return false;
    return true;
}

void mk::ResourceLoader::log_resources()
{
    log_info("\nlisting resource loader contents: ");
    for (std::map<const char *, ResourcePointer>::iterator it = resources.begin(); it != resources.end(); ++it)
    {
        fst("key:" << it->first << " value:" << it->second);
    }
}