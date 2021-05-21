#pragma once
#include "types.h"

namespace mk
{
    struct StateManager
    {
        void *current_texture = nullptr;
        void *current_shader = nullptr;
        unsigned int current_vao = 0;
        mk::Mat4 current_projection_matrix = mk::Mat4(0);

        void change_vao(unsigned int id);
    };
} //namespace mk