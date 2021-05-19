#include "engine.h"
#include "resource_loader.h"
#include "sprite_renderer.h"

class Game : public mk::Engine
{
    mk::SpriteRenderer sprite_renderer;
    mk::Sprite sprite;

    void start()
    {
        sprite_renderer.init();

        mk::ResourceLoader::load_texture("textures/happy.png", "happy");
        sprite.load("happy", {0, 0, 256, 256});
    }

    void update(float delta)
    {
    }

    void render()
    {

        for (int i = 0; i < 500; i++)
            sprite_renderer.draw(sprite, input.mouse_position);

        sprite_renderer.flush();
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}