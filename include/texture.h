#pragma once
#include "opengl_object.h"
#include <glm/glm.hpp>

namespace mk
{
    class Texture : public mk::OpenGLObject
    {
    public:
        int width, height, channels; //stores image information

        Texture() {}
        bool load(const char *path);
        void use();
    };
} // namespace mk