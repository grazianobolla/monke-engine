#pragma once
#include <glm/glm.hpp>

namespace mk
{
    struct StateManager
    {
        void *current_texture = nullptr;
        unsigned int current_vao = 0;
        glm::mat4 current_projection_matrix = glm::mat4(0);

        void change_vao(unsigned int id);
    };
} //namespace mk