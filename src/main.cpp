#include "engine.h"
#include "resource_loader.h"

class Game : public mk::Engine
{
    mk::Sprite sprite;

    void start()
    {
        mk::ResourceLoader::load_texture("textures/sheet.png", "sheet");
        sprite.load("sheet");
    }

    void update(float delta) {}

    void render()
    {
        for (int i = 0; i < 50000; i++)
            renderer.draw(sprite, input.mouse_position, {1, 1});
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}