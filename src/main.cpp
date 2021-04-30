#include "engine.h"
#include "resource_loader.h"
#include "animated_sprite.h"

class Game : public mk::Engine
{
    mk::AnimatedSprite anim_sprite;

    void start()
    {
        //load texture on the engine
        mk::ResourceLoader::load_texture("textures/dude.png", "dude");

        //bind the texture to the sprite and select a rectangle, top-left is 0, 0
        anim_sprite.load("dude", {0, 0, 32, 19});
        anim_sprite.configure_animation(3, 0.2f, {32, 19});
        anim_sprite.play();
    }

    void update(float delta)
    {
        anim_sprite.draw(input.mouse_position, {10, 10});
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}