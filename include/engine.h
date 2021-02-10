#pragma once
#include "display.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace mk
{
    class Engine
    {
    public:
        mk::Display display;

        Engine(){};
        void run(int width, int height, const char *title);
        virtual void start() = 0;
        virtual void update() = 0;

    protected:
        glm::mat4 projection;
    };
} // namespace mk