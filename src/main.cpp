#include "core/engine.h"
#include "core/resource_loader.h"
#include "core/signal.h"

class Game : public mk::Engine
{
    mk::Sprite sprite;

    void start()
    {
        //load the texture into memory
        mk::ResourceLoader::load_texture("textures/happy.png", "happy");
        sprite.load("happy");
    }

    void update(float delta) {}

    void render()
    {
        renderer.draw(sprite, input.get_mouse_pos(), {.1f, .1f});
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}