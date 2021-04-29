#include "animated_sprite.h"
#include "engine.h"

#include <GLFW/glfw3.h>

void mk::AnimatedSprite::update()
{
    this->current_frame = static_cast<int>(glfwGetTime() * (1 / this->frame_duration)) % this->frame_count;

    if (this->playing == true && current_frame != last_frame)
    {
        int newX = current_frame * this->frame_size.x;

        this->update_rect({newX, this->texture_coordinates.y, this->texture_coordinates.w, this->texture_coordinates.z});
        this->last_frame = current_frame;
    }
}

void mk::AnimatedSprite::play()
{
    this->playing = true;
}

void mk::AnimatedSprite::stop()
{
    this->playing = false;
}

void mk::AnimatedSprite::configure_animation(int frames, float duration, const glm::vec2 &frame_siz)
{
    this->frame_count = frames;
    this->frame_duration = duration;
    this->frame_size = frame_siz;

    mk::Engine::add_tickable_element(this);
}