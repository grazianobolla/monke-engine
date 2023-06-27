#include "monke/core/engine.h"
#include "monke/core/imgui_utils.h"
#include "monke/external/imgui/imgui.h"

class Game : public mk::Engine
{
    mk::Sprite player, player1, player2;
    mk::Texture tex;
    mk::Vector2 cam_pos;

    void start()
    {
        player.load("textures/dude.png", {0, 0}, 0, {2, 2}, {0, 0, 17, 19});
        player1.load("textures/dude.png", {100, 100}, 0, {2, 2}, {0, 0, 17, 19});
        player2.load("textures/dude.png", {200, 200}, 0, {2, 2}, {0, 0, 17, 19});
        tex.load("textures/sheet.png");
    }

    // called on input
    void on_input(mk::InputEvent event)
    {
        if (event.action == GLFW_REPEAT)
            return;
    }

    // every frame
    void update(float delta)
    {
        ImGui::Begin("Camera Test", NULL, ImGuiWindowFlags_None);
        ImGui::DragFloat("X", &cam_pos.x, 1, -300, 300);
        ImGui::DragFloat("Y", &cam_pos.y, 1, -300, 300);
        if (ImGui::Button("Reset"))
        {
            cam_pos = {0, 0};
        }
        ImGui::End();

        mk::Engine::camera.position = cam_pos;
    }

    void render(mk::Renderer *renderer)
    {
        mk::render_engine_data();

        renderer->draw(player);

        for (int x = 128; x < 800; x += 32)
            for (int y = 128; y < 600; y += 32)
                renderer->draw(&tex, {0, 0, 32, 32}, {x, y}, {1, 1});

        renderer->draw(player1);
        renderer->draw(player2);
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Mexicali The Game");
    return 0;
}