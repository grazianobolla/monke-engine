#include "core/engine.h"
#include "core/resource_loader.h"
#include "core/signal.h"

class Game : public mk::Engine
{
    mk::Sprite sprite, sprite_sheet;

    void start()
    {
        // load the texture into memory
        sprite.load("textures/happy.png");
        sprite_sheet.load("textures/happy.png");
    }

    void update(float delta)
    {
        if (input.is_key_pressed(GLFW_KEY_U))
        {
            mk::ResourceLoader::log_resources();
            log_info("\n");
        }
    }

    void render()
    {
        renderer.draw(sprite, input.get_mouse_pos(), {.1f, .1f});
        renderer.draw(sprite_sheet, input.get_mouse_pos());
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}