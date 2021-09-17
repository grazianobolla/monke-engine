#pragma once
#include <vector>

#define SignalEvent const char * //TODO: for now

namespace mk
{
    class Emitter; //forward declaration

    class Listener
    {
    public:
        virtual ~Listener();
        virtual void OnNotify(SignalEvent event) = 0;

        //currently connected emmiters
        std::vector<Emitter *> connected_emmiters;
    };

    class Emitter
    {
    public:
        void Emit(SignalEvent event);
        void Connect(Listener *listener);
        void Disconnect(Listener *listener);

        //currently connected listeners
        std::vector<Listener *> listeners;
    };
}