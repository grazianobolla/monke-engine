#include "engine.h"
#include "sprite.h"
#include "resource_loader.h"
#include "animated_sprite.h"

class Game : public mk::Engine
{
    mk::AnimatedSprite as;

    void start()
    {
        mk::ResourceLoader::load_texture("textures/sheet.png", "sheet_texture");
        mk::ResourceLoader::load_texture("textures/grass.png", "grass");
        mk::ResourceLoader::load_shader("shaders/vertex.glsl", "shaders/fragment.glsl", "default_shader");

        as.load("sheet_texture", "default_shader");
        as.configure_animation(4, 0.1f, {32, 32});
        as.play();
    }

    float counter = 0;
    void update(float delta)
    {
        as.draw(input.mouse_position);
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}