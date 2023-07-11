#include "monke/core/engine.h"
#include "monke/core/debug.h"

class Game : public mk::Engine
{
    mk::Debug debug;

    void start()
    {
        debug.initialize(this);
    }

    void on_input(mk::InputEvent event)
    {
    }

    void update(float delta)
    {
        debug.update(delta);
    }

    void render(mk::Renderer *renderer)
    {
        debug.render_debug_data();
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Mexicali The Game", true);
    return 0;
}