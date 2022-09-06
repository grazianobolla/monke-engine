#pragma once
#include "core/shader.h"
#include "core/texture.h"

#include <map>

namespace mk
{
    typedef void *ResourcePointer;

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
        static mk::Texture *load_texture(const char *path);

        static ResourcePointer get(const char *resource_name);
        static void log_resources();

    private:
        static std::map<const char *, ResourcePointer> resources;
        static bool exists(const char *key);
        static void delete_resource(const char *resource_name, RESOURCE_TYPE resource_type);
    };
} // namespace mk