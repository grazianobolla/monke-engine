#include "engine.h"
#include "resource_loader.h"
#include "animated_sprite.h"

class Game : public mk::Engine
{
    mk::AnimatedSprite anim_sprite;

    void start()
    {
        //load texture on the engine
        mk::ResourceLoader::load_texture("textures/sheet.png", "sheet_texture");

        //bind the texture to the sprite and select a rectangle, top-left is 0, 0
        anim_sprite.load("sheet_texture", {0, 0, 32, 32});
        anim_sprite.configure_animation(4, 0.5f, {32, 32});
    }

    void update(float delta)
    {
        if (input.mouse_button[0])
        {
            mk::AnimatedSprite anim_sprite;
            anim_sprite.load("sheet_texture", {0, 0, 32, 32});
            anim_sprite.configure_animation(4, 0.5f, {32, 32});
            anim_sprite.draw(input.mouse_position);
        }
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}