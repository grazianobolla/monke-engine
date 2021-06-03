#include "engine.h"
#include "resource_loader.h"

using namespace mk;

class Game : public Engine
{
    Sprite sprite, sprite1;
    Vector2 pos = {0, 0}, mouse;

    void start()
    {
        //load the texture into memory
        ResourceLoader::load_texture("textures/sheet.png", "sheet");
        ResourceLoader::load_texture("textures/happy.png", "happy");
        sprite.load("sheet");
        sprite1.load("happy");

        mouse = input.get_mouse_pos();
    }

    int interval = 0;
    void update(float delta)
    {
        if (input.key_states[GLFW_KEY_F1])
        {
            if (interval == 0)
                interval = 1;
            else
                interval = 0;
            glfwSwapInterval(interval);
        }
        if (input.key_states[GLFW_KEY_RIGHT])
            pos.x += 1000 * delta;
        if (input.key_states[GLFW_KEY_LEFT])
            pos.x -= 1000 * delta;
        pos.y = 100;

        mouse = input.get_mouse_pos();
    }

    void render()
    {
        renderer.draw(sprite, mouse);
        renderer.draw(sprite1, pos, {0.2f, 0.2f});
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}
