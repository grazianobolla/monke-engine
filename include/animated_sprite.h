#pragma once
#include "sprite.h"
#include "tickable.h"

namespace mk
{
    class AnimatedSprite : public Tickable, public Sprite
    {
    private:
        glm::vec2 frame_size;
        using Sprite::update_rect;
        int last_frame = 0;

    public:
        int current_frame = 0, frame_count = 0;
        float frame_duration = 0;
        bool playing = false;

        void play();
        void stop();
        void configure_animation(int frames, float duration, const glm::vec2 &frame_siz);
        void update();
    };
}; //namespace mk