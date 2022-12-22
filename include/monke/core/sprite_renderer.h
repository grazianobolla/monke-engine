#pragma once
#include "monke/core/sprite.h"
#include "monke/core/shader.h"
#include "monke/core/types.h"
#include "monke/external/glm/glm.hpp"

namespace mk
{
    class SpriteRenderer
    {
    public:
        static const int VERTEX_SIZE_IN_FLOATS = 4; // 2POS 2TEX
        static const int VERTEX_PER_SPRITE = 6;
        static const int SPRITE_SIZE_IN_FLOATS = (VERTEX_SIZE_IN_FLOATS * VERTEX_PER_SPRITE);

        ~SpriteRenderer() {}

        void initialize();
        void draw(const mk::Sprite &sprite);

    private:
        mk::Shader *shader = nullptr;
        unsigned int vao_id = 0, vbo_id = 0;

        glm::mat4 calculateTransform(const mk::Sprite &sprite);
    };
} // namespace mk