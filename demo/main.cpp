#include "monke/core/engine.h"
#include "monke/core/debug.h"

class Game : public mk::Engine
{
    mk::Debug debug;
    mk::Texture texture;

    void start()
    {
        debug.initialize(this);
        texture.load("resources/textures/dude.png");
    }

    void on_input(mk::InputEvent event)
    {
        if (event.type == mk::Input::MOUSE && event.action == GLFW_PRESS && event.code == GLFW_MOUSE_BUTTON_1)
        {
            texture.mirror_x = !texture.mirror_x;
        }
    }

    void update(float delta)
    {
        debug.update(delta);
        this->camera.position += input.get_direction() * delta * 128;
    }

    void render(mk::Renderer *renderer)
    {
        debug.render_debug_data();

        renderer->draw(&texture, {0, 0, 32, 32}, {0, 0}, {2, 2});
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Mexicali The Game", true);
    return 0;
}