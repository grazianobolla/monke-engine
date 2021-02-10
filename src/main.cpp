#include "engine.h"
#include "sprite.h"
#include "texture.h"
#include "resource_loader.h"

class Game : public mk::Engine
{
    mk::Sprite sprite;
    void start()
    {
        mk::ResourceLoader::load_texture("textures/happy.png", "happy_texture");
        mk::ResourceLoader::load_shader("shaders/vertex.glsl", "shaders/fragment.glsl", "default_shader");

        sprite.load((mk::Texture *)mk::ResourceLoader::get("happy_texture"),
                    (mk::Shader *)mk::ResourceLoader::get("default_shader"), this->projection);
    }

    void update()
    {
        sprite.draw({10, 10}, {.3, .3});
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "OpenGL Window!");
    return 0;
}