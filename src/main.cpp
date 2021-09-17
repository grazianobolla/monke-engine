#include "core/engine.h"
#include "core/resource_loader.h"
#include "core/signal.h"

struct Player : public mk::Emitter
{
    mk::Sprite sprite;
    mk::Vector2f position;

    void attack()
    {
        fst("ATTACK!");
        Emit("attacked");
    }
};

class MultiplayerGame : public mk::Listener
{
    void OnNotify(SignalEvent event)
    {
        if (event == "attacked")
        {
            fst("a player just attacked!");
        }

        if (event == "die")
        {
            fst("a player just died");
        }
    }

public:
    ~MultiplayerGame()
    {
        fst("delete on mp");
    }
};

class Game : public mk::Engine
{
    int a = 1;
    int *b = &a;
    int *c = b;

    mk::Sprite sprite;

    Player player;
    MultiplayerGame *game;

    void start()
    {
        game = new MultiplayerGame();
        //load the texture into memory
        mk::ResourceLoader::load_texture("textures/happy.png", "happy");
        sprite.load("happy");

        player.Connect(game);
    }

    void update(float delta)
    {
        if (input.is_key_pressed(GLFW_KEY_SPACE))
            player.attack();

        if (input.is_key_pressed(GLFW_KEY_A) && game != nullptr)
        {
            delete game;
            game = nullptr;
        }
    }

    void render()
    {
        renderer.draw(sprite, input.get_mouse_pos(), {.1f, .1f});
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Monke Engine OpenGL");
    return 0;
}