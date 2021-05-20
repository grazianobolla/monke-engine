#pragma once
#include "sprite.h"
#include "shader.h"

#include <glm/glm.hpp>

#define MAX_SPRITES 5000
#define SPRITE_SIZE_IN_FLOATS 24 //6 vertexs, each vertex is 4 floats
#define VERTEX_SIZE_IN_FLOATS 4  //2 for position and 2 for texture
#define VERTEX_PER_SPRITE 6

namespace mk
{
    struct Vertex
    {
        float data[4];
    };

    class SpriteRenderer
    {
    public:
        SpriteRenderer();
        ~SpriteRenderer() {}

        void begin();
        void draw(const Sprite &sprite, glm::vec2 position, glm::vec2 scale = {1, 1});
        void flush();

        void initialize();

    private:
        float vertex_data[MAX_SPRITES * SPRITE_SIZE_IN_FLOATS];
        unsigned int sprite_count = 0;

        //opengl buffers
        unsigned int vao_id = 0, vbo_id = 0;

        //if this is true, there is data on the buffer waiting to be sended
        bool has_data = false;

        mk::Shader *shader = nullptr;
        mk::Texture *texture = nullptr;

        void push_sprite_data(const Sprite &sprite, glm::vec2 position, glm::vec2 scale);
        void check_flush(mk::Texture *);
    };
} //namespace mk