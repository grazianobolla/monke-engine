#include "engine.h"
#include "sprite.h"
#include "resource_loader.h"

static void input_cb(GLFWwindow *window, int key, int scancode, int action, int mods);

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

        if (input.key_states[GLFW_KEY_D] > 0)
        {
            pos.x += 500 * delta;
        }

        if (input.key_states[GLFW_KEY_A] > 0)
        {
            pos.x -= 500 * delta;
        }

        if (input.key_states[GLFW_KEY_W] > 0)
        {
            pos.y -= 500 * delta;
        }

        if (input.key_states[GLFW_KEY_S] > 0)
        {
            pos.y += 500 * delta;
        }

        fst("x:" << pos.x << " y:" << pos.y << " mouse: x:" << input.mouse_position.x << " y:" << input.mouse_position.y);
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}