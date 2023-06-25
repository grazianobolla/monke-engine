#include "monke/core/engine.h"
#include "monke/external/imgui/imgui.h"

class Game : public mk::Engine
{
    mk::Sprite player, player1;
    mk::Texture tex;

    void start()
    {
        player.load("textures/dude.png", {0, 0}, 0, {3, 3}, {0, 0, 17, 19});
        player1.load("textures/dude.png", {0, 0}, 0, {3, 3}, {0, 0, 17, 19});
        tex.load("textures/sheet.png");
    }

    // called on input
    void on_input(mk::InputEvent event)
    {
        if (event.action == GLFW_REPEAT)
            return;

        if (event.action == GLFW_PRESS && event.code == GLFW_KEY_SPACE)
        {
            player.texture->mirror_x = !player.texture->mirror_x;
            player.texture->mirror_y = !player.texture->mirror_y;
        }
    }

    // every frame
    void update(float delta)
    {
        player.position = input.get_mouse_pos();
        player1.position = input.get_mouse_pos();
        player.rotation += delta * 128;
        player1.rotation -= delta * 128;
    }

    void render(mk::Renderer *renderer)
    {
        renderer->draw(player);

        for (int y = 0; y < 18; y++)
        {
            for (int x = 0; x < 12; x++)
            {
                renderer->draw(&tex, {((x + y) % 4) * 32, 0, 32, 32}, {x * 32, y * 32}, {1, 1});
            }
        }

        for (int y = 0; y < 18; y++)
        {
            for (int x = 10; x < 25; x++)
            {
                renderer->draw(&tex, {0, 0, 32, 32}, {x * 32, y * 32}, {1, 1});
            }
        }

        renderer->draw(player1);
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Mexicali The Game");
    return 0;
}