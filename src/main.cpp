#include "core/engine.h"
#include "core/resource_loader.h"
#include "core/signal.h"

class Game : public mk::Engine
{
    mk::Sprite sprite;
    mk::Vector2 pos;

    void start()
    {
        // load the texture into memory
        sprite.load("textures/sheet.png", {0, 0, 16, 16});
    }

    void update(float delta)
    {
    }

    void render()
    {
        renderer.draw(sprite, {0, 0}, {1, 1});
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}