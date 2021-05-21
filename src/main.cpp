#include "engine.h"
#include "resource_loader.h"

using namespace mk;

class Game : public Engine
{
    Sprite sprite, sprite1;

    void start()
    {
        //load the texture into memory
        ResourceLoader::load_texture("textures/sheet.png", "sheet");
        ResourceLoader::load_texture("textures/happy.png", "happy");
        sprite.load("sheet");
        sprite1.load("happy");
    }

    void update(float delta) {}

    void render()
    {
        renderer.draw(sprite, input.mouse_position);
        renderer.draw(sprite1, {100, 100});
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}
