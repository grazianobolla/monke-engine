#include "engine.h"
#include "resource_loader.h"
#include "sprite.h"

class Game : public mk::Engine
{
    mk::Sprite sprite;

    void start()
    {
        mk::ResourceLoader::load_texture("textures/sheet.png", "sheet_texture");
        mk::ResourceLoader::log_resources();

        sprite.load("sheet_texture", {0, 32, 32, 32});
    }

    void update(float delta)
    {
        sprite.draw(input.mouse_position);
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}