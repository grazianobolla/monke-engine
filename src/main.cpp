#include "engine.h"
#include "resource_loader.h"
#include "animated_sprite.h"
#include "signal.h"

class Game : public mk::Engine
{
    mk::AnimatedSprite anim_sprite[3];

    void start()
    {
        mk::ResourceLoader::load_texture("textures/dude.png", "dude");

        for (int i = 0; i < 3; i++)
        {
            anim_sprite[i].load("dude", {0, 0, 17, 19});
            anim_sprite[i].configure_animation(3, 0.1f, {17, 19});
        }
    }

    void update(float delta)
    {
        for (int i = 0; i < 3; i++)
        {
            if (input.key_states[GLFW_KEY_RIGHT] == input.PRESSED)
                anim_sprite[i].play(false);
            else if (input.key_states[GLFW_KEY_LEFT] == input.PRESSED)
                anim_sprite[i].play(true);
            else
                anim_sprite[i].stop();

            anim_sprite[i].draw(input.mouse_position, 0, {7, 7});
        }
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}