#include "monke/core/signal.h"
#include "monke/core/log.h"

#include <algorithm>

void mk::Emitter::Emit(const char *event)
{
    for (Listener *listener : this->listeners)
        listener->OnNotify(event);
}

void mk::Emitter::Connect(Listener *listener)
{
    listener->connected_emmiters.push_back(this);
    listeners.push_back(listener);
}

void mk::Emitter::Disconnect(Listener *listener)
{
    listeners.erase(std::remove(listeners.begin(), listeners.end(), listener));
}

mk::Listener::~Listener()
{
    //if the listener is deleted, we remove it from all its connected emmiters
    //this way we dont call a unallocated pointer
    for (Emitter *emitter : connected_emmiters)
        emitter->Disconnect(this);
}