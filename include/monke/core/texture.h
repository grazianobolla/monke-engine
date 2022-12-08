#pragma once

namespace mk
{
    class Texture
    {
    public:
        unsigned int id = 0;
        int width, height, channels; //stores image information

        Texture() {}
        bool load(const char *path);
        void use();
    };
} // namespace mk