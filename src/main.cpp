#include "engine.h"
#include "resource_loader.h"

using namespace mk;

class Game : public Engine
{
    Sprite sprite;

    void start()
    {
        //load the texture into memory
        ResourceLoader::load_texture("textures/grass.png", "grass");

        //attach texture to the sprite
        sprite.load("grass");
    }

    void update(float delta) {}

    void render()
    {
        //render the sprite over our cursor
        renderer.draw(sprite, input.mouse_position);
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}