#include "engine.h"
#include "resource_loader.h"

class Game : public mk::Engine
{
    mk::Sprite sprite;
    mk::Vector2 pos = {100, 100}, mouse;

    void start()
    {
        //load the texture into memory
        mk::ResourceLoader::load_texture("textures/happy.png", "happy");
        sprite.load("happy");

        mouse = input.get_mouse_pos();
    }

    void update(float delta)
    {
        mouse = input.get_mouse_pos();
        pos += mk::math::Normalize((mouse - pos)) * delta * 1000.0f;
    }

    void render()
    {
        renderer.draw(sprite, pos, {.1f, .1f});
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}
