#include "engine.h"
#include "resource_loader.h"
#include "animated_sprite.h"
#include "signal.h"

class Game : public mk::Engine
{
    mk::AnimatedSprite anim_sprite;
    mk::Sprite sprite;

    void start()
    {
        mk::ResourceLoader::load_texture("textures/dude.png", "dude");

        anim_sprite.load("dude", {0, 0, 17, 19});
        anim_sprite.configure_animation(3, 0.1f, {17, 19});

        sprite.load("dude", {10, 10, 7, 9});
    }

    void update(float delta)
    {
        if (input.key_states[GLFW_KEY_RIGHT] == input.PRESSED)
            anim_sprite.play(false);
        else if (input.key_states[GLFW_KEY_LEFT] == input.PRESSED)
            anim_sprite.play(true);
        else
            anim_sprite.stop();

        anim_sprite.draw({200, 200}, {5, 5});

        //sprite.draw(input.mouse_position, {15, 15});
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}