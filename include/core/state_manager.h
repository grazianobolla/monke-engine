#pragma once
#include "external/glm/glm.hpp"

namespace mk
{
    class StateManager
    {
    private:
        static StateManager *pointer;
        ~StateManager();

    public:
        static StateManager *get();

        void *current_texture = nullptr;
        void *current_shader = nullptr;
        unsigned int current_vao = 0;
        glm::mat4 current_projection_matrix = glm::mat4(0);
    };
} //namespace mk