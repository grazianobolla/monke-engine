#pragma once
#include "monke/core/sprite.h"
#include "monke/core/shader.h"
#include "monke/core/types.h"

#include "monke/external/glm/glm.hpp"

#define MAX_SPRITES 5000        // max amount of sprites allowed until flush
#define VERTEX_SIZE_IN_FLOATS 4 // 2 for position and 2 for texture
#define VERTEX_PER_SPRITE 6

#define SPRITE_SIZE_IN_FLOATS (VERTEX_SIZE_IN_FLOATS * VERTEX_PER_SPRITE)

namespace mk
{
    class Renderer
    {
    public:
        Renderer();
        ~Renderer() {}

        void initialize();
        void begin();
        void draw(const mk::Sprite &sprite);
        void draw(mk::Texture *texture, mk::Rectf texture_rect, mk::Vector2 position, mk::Vector2 scale);
        void flush();

    private:
        float vertex_data[MAX_SPRITES * SPRITE_SIZE_IN_FLOATS];
        unsigned int sprite_count = 0;

        // opengl buffers
        unsigned int vao_id = 0, vbo_id = 0;

        // if this is true, there is data on the buffer waiting to be sended
        bool has_data = false;

        mk::Shader *shader = nullptr;
        mk::Texture *texture = nullptr;

        void push_draw_data(mk::Texture *texture, mk::Rectf texture_rect, mk::Vector2 position, mk::Vector2 scale);
        void check_flush(mk::Texture *new_texture);
    };
} // namespace mk