#include "monke/core/engine.h"
#include "monke/core/debug.h"

class Game : public mk::Engine
{
    mk::Debug debug;
    mk::Texture texture;
    mk::Sprite player;

    int x = 1;

    void start()
    {
        debug.initialize(this);
        texture.load("resources/textures/dude.png");
        player.load("resources/textures/dude.png", {0, 0}, 0, {4, 4}, {0, 0, 17, 19});
    }

    void on_input(mk::InputEvent event)
    {
        if (event.type == mk::Input::MOUSE && event.action == GLFW_PRESS && event.code == GLFW_MOUSE_BUTTON_1)
        {
            player.scale.x *= -1;
            player.scale.y *= -1;
        }
    }

    void update(float delta)
    {
        debug.update(delta);
        this->camera.position += input.get_direction() * delta * 128;
        player.position = input.get_mouse_pos();
        player.rotation += 1;
    }

    void render(mk::Renderer *renderer)
    {
        debug.render_debug_data();
        renderer->draw(player);
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Mexicali The Game", true);
    return 0;
}