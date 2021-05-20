#include "engine.h"
#include "resource_loader.h"

class Game : public mk::Engine
{
    mk::Sprite sprite, sprite1;

    void start()
    {
        mk::ResourceLoader::load_texture("textures/sheet.png", "sheet");
        mk::ResourceLoader::load_texture("textures/happy.png", "happy");
        sprite.load("sheet");
        sprite1.load("happy");
    }

    void update(float delta) {}

    void render()
    {
        renderer.draw(sprite, input.mouse_position, {1, 1});
        renderer.draw(sprite1, {200, 200}, {.5f, .5f});
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}