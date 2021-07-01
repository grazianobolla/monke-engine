#include "core/state_manager.h"
#include "core/log.h"

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

mk::StateManager::~StateManager()
{
    delete pointer;
}