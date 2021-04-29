#include "engine.h"
#include "resource_loader.h"
#include "sprite.h"

class Game : public mk::Engine
{
    //create sprite
    mk::Sprite sprite;

    void start()
    {
        //load texture on the engine
        mk::ResourceLoader::load_texture("textures/sheet.png", "sheet_texture");

        //bind the texture to the sprite and select a rectangle, top-left is 0, 0
        sprite.load("sheet_texture", {0, 0, 32, 32});
    }

    void update(float delta)
    {
        //draw the sprite at the current mouse position
        sprite.draw(input.mouse_position);
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}