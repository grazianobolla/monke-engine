#include "state_manager.h"
#include "log.h"

#include <glad/glad.h>
void mk::StateManager::change_vao(unsigned int id)
{
    if (id != this->current_vao)
    {
        glBindVertexArray(id);
        this->current_vao = id;
    }
}