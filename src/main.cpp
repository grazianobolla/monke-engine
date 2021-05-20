#include "engine.h"
#include "resource_loader.h"

using namespace mk;
using namespace glm;

class Game : public Engine
{
    Sprite sprite;
    vec2 display_size;

    void start()
    {
        //load the texture into memory
        ResourceLoader::load_texture("textures/sheet.png", "sheet");

        //attach texture to the sprite
        sprite.load("sheet");

        //get the display size
        display_size = display.get_size();
    }

    void update(float delta) {}

    void render()
    {
        //iterate the screen
        for (float x = 0; x < display_size.x; x += 32)
            for (float y = 0; y < display_size.y; y += 32)
            {
                //randomly set the sprite TextureRect
                //each frame is 32 pixels, and they are aligned on the X axis
                int frame = (rand() % 4) * 32;
                sprite.texture_rect = {frame, 0, 32, 32};

                //send the draw call
                renderer.draw(sprite, {x, y});
            }
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}
