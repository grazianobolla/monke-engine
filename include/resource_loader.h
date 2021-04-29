#pragma once
#include "shader.h"
#include "texture.h"

#include <map>

namespace mk
{
    class ResourceLoader
    {
    public:
        enum RESOURCE_TYPE
        {
            SHADER,
            TEXTURE
        };

        ResourceLoader() {}
        static void load_shader(const char *vert_path, const char *frag_path, const char *key);
        static void load_texture(const char *path, const char *key);
        static void *get(const char *resource_name);
        static void delete_resource(const char *resource_name, RESOURCE_TYPE resource_type);
        static void log_resources();

    private:
        static std::map<const char *, void *> resources;
        static bool exists(const char *key);
    };
} // namespace mk