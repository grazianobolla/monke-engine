#pragma once

namespace mk
{
    class Texture
    {
    public:
        int width, height, channels; //stores image information

        Texture() {}
        bool load(const char *path);
        void use();

    private:
        unsigned int texture_id;
    };
} // namespace mk