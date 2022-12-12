#include "monke/core/engine.h"
#include "monke/core/sprite.h"
#include "monke/core/shader.h"
#include "monke/types/rect.h"

#include "monke/external/glm/glm.hpp"
#include "monke/external/glm/gtc/matrix_transform.hpp"

class Game : public mk::Engine
{
    mk::Sprite sprite;
    mk::Texture tex;
    mk::Shader shader;

    void start()
    {
        sprite.load("textures/sheet.png");
        tex.load("textures/sheet.png");
    }

    void on_input(mk::InputEvent event)
    {
    }

    void update(float delta)
    {
        sprite.position = input.get_mouse_pos();
    }

    void render()
    {
        sprite_renderer.draw(sprite);
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(512, 512, "Monke Engine Demo");
    return 0;
}