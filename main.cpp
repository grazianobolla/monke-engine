#include "monke/core/engine.h"
#include "monke/external/imgui/imgui.h"

class Game : public mk::Engine
{
    mk::Sprite player;
    bool m = false;

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    void start()
    {
        player.load("textures/dude.png", {0, 0}, 0, {3, 3}, {0, 0, 17, 19});
    }

    // called on input
    void on_input(mk::InputEvent event)
    {
        if (event.action == GLFW_REPEAT)
            return;

        if (event.action == GLFW_PRESS && event.code == GLFW_KEY_SPACE)
        {
            player.texture->mirror_x = !player.texture->mirror_x;
            player.texture->mirror_y = !player.texture->mirror_y;
        }

        if (event.type = mk::Input::MOUSE && event.action == GLFW_PRESS && event.code == GLFW_MOUSE_BUTTON_1)
        {
            player.rotation += 16;
        }
    }

    // every frame
    void update(float delta)
    {
        player.position = input.get_mouse_pos();
    }

    void render(mk::Renderer *renderer)
    {
        renderer->draw(player);

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");          // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);             // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.run(800, 600, "Mexicali The Game");
    return 0;
}