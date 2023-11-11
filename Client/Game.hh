#pragma once

#include <Renderer.hh>

#include <inttypes.h>

namespace gardn {
    class Game {
    public:
        uint32_t test;
        Game();
        void Tick(float);
    };
    extern Game game;
    extern renderer::Renderer renderer;
}