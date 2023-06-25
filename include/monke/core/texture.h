#pragma once

namespace mk
{
    class Texture
    {
    public:
        unsigned int id = 0;
        bool loaded = false;

        bool mirror_x = false;
        bool mirror_y = false;

        Texture() {}
        bool load(const char *path);
        void use();

        int get_width();
        int get_height();

    private:
        int width, height, channels; // stores image information
    };
} // namespace mk