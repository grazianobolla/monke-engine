#include "engine.h"
#include "sprite.h"
#include "resource_loader.h"

class Game : public mk::Engine
{
    mk::Sprite sprite, sprite_1;

    void start()
    {
        mk::ResourceLoader::load_texture("textures/happy.png", "happy_texture");
        mk::ResourceLoader::load_texture("textures/grass.png", "grass_texture");
        mk::ResourceLoader::load_shader("shaders/vertex.glsl", "shaders/fragment.glsl", "default_shader");

        sprite.load("happy_texture", "default_shader");
        sprite_1.load("grass_texture", "default_shader");
    }

    glm::vec2 pos;
    void update(float delta)
    {
        sprite_1.draw(pos);
        sprite.draw(input.mouse_position, {.3, .3});

        if (input.key_states[GLFW_KEY_D] == mk::Input::PRESSED)
        {
            pos.x += 500 * delta;
        }

        if (input.key_states[GLFW_KEY_A] == mk::Input::PRESSED)
        {
            pos.x -= 500 * delta;
        }

        if (input.key_states[GLFW_KEY_W] == mk::Input::PRESSED)
        {
            pos.y -= 500 * delta;
        }

        if (input.key_states[GLFW_KEY_S] == mk::Input::PRESSED)
        {
            pos.y += 500 * delta;
        }
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}