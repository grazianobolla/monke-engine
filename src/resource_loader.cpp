#include "resource_loader.h"
#include "log.h"

std::map<const char *, void *> mk::ResourceLoader::resources;

void mk::ResourceLoader::load_shader(const char *vert_path, const char *frag_path, const char *key)
{
    if (exists(key))
        return;

    mk::Shader *temp_shader = new mk::Shader();

    if (temp_shader->load(vert_path, frag_path) == false)
    {
        log_info("error while loading " << key << " shader (maybe file does not exist)");
        return;
    }

    resources.insert({key, static_cast<void *>(temp_shader)});
}

void mk::ResourceLoader::load_texture(const char *path, const char *key)
{
    if (exists(key))
        return;

    mk::Texture *temp_texture = new mk::Texture();

    if (temp_texture->load(path) == false)
    {
        log_info("error while loading " << key << " texture (maybe file does not exist)");
        return;
    }

    resources.insert({key, static_cast<void *>(temp_texture)});
}

void *mk::ResourceLoader::get(const char *resource_name)
{
    if (exists(resource_name) == false)
    {
        log_info("cant get resource " << resource_name << " it does not exist");
        return NULL;
    }

    return resources.at(resource_name);
}

bool mk::ResourceLoader::exists(const char *key)
{
    if (resources.find(key) != resources.end())
    {
        return true;
    }
    return false;
}

void mk::ResourceLoader::delete_resource(const char *resource_name, RESOURCE_TYPE resource_type)
{
    //for debug
    std::string resource_type_string(resource_type == RESOURCE_TYPE::SHADER ? "shader " : "texture ");

    if (exists(resource_name) == true)
    {
        void *resource_pointer = resources.at(resource_name);
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