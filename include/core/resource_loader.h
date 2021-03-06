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
        static void load_texture(const char *path, const char *key);
        static ResourcePointer get(const char *resource_name);
        static void delete_resource(const char *resource_name, RESOURCE_TYPE resource_type);
        static void log_resources();

    private:
        static std::map<const char *, ResourcePointer> resources;
        static bool exists(const char *key);
    };
} // namespace mk