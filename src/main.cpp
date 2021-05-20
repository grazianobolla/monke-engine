#include "engine.h"
#include "resource_loader.h"
#include "sprite_renderer.h"

class Game : public mk::Engine
{
    mk::SpriteRenderer sprite_renderer;
    mk::Sprite sprite, sprite1;

    void start()
    {
        sprite_renderer.init();

        mk::ResourceLoader::load_texture("textures/happy.png", "happy");
        mk::ResourceLoader::load_texture("textures/sheet.png", "sheet");
        sprite.load("sheet", {0, 0, 32, 32});
        sprite1.load("happy", {0, 0, 512, 512});
    }

    void update(float delta) {}

    void render()
    {
        sprite_renderer.begin();
        sprite_renderer.draw(sprite, {60, 60}, {1, 1});
        sprite_renderer.draw(sprite1, input.mouse_position, {0.15f, 0.15f});
        sprite_renderer.end();
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}