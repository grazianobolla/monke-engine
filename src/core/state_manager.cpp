#include "state_manager.h"
#include "log.h"

#include <glad/glad.h>

mk::StateManager *mk::StateManager::pointer = nullptr;
mk::StateManager *mk::StateManager::get()
{
    if (pointer == nullptr)
    {
        pointer = new mk::StateManager;
        log_info("created state_manager pointer");
    }

    return pointer;
}

void mk::StateManager::change_vao(unsigned int id)
{
    if (id != this->current_vao)
    {
        glBindVertexArray(id);
        this->current_vao = id;
    }
}

mk::StateManager::~StateManager()
{
    delete pointer;
}