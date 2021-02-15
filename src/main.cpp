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

    void update()
    {
        double x, y;
        glfwGetCursorPos(this->display.window, &x, &y);
        sprite_1.draw({200, 60});
        sprite.draw({x, y}, {.3, .3});
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}