#include "core/engine.h"
#include "core/resource_loader.h"
#include "core/signal.h"

class Game : public mk::Engine
{
    mk::Sprite sprite, sprite_sheet;
    mk::Vector2 pos;

    void start()
    {
        // load the texture into memory
        sprite.load("textures/happy.png");
        sprite_sheet.load("textures/happy.png");
    }

    void update(float delta)
    {
        if (input.is_mouse_pressed(GLFW_MOUSE_BUTTON_1))
            pos += mk::Vector2(64, 16) * delta;

        fst(pos.to_string());
    }

    void render()
    {
        renderer.draw(sprite_sheet, input.get_mouse_pos() + pos, mk::Vector2(0.1f, 0.1f));
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}