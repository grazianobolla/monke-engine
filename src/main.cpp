#include "engine.h"
#include "sprite.h"
#include "resource_loader.h"

class Game : public mk::Engine
{
    mk::Sprite sprite;

    void start()
    {
        mk::ResourceLoader::load_texture("textures/sheet.png", "sheet_texture");
        mk::ResourceLoader::load_shader("shaders/vertex.glsl", "shaders/fragment.glsl", "default_shader");

        sprite.load("sheet_texture", "default_shader");
    }

    void update(float delta)
    {
        sprite.draw_partial(input.mouse_position, {32, 32, 32, 32}, {3, 3});
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}