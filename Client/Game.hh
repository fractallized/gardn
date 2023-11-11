#pragma once

#include <inttypes.h>

#include <Renderer.hh>
#include <Shared/Protocol.hh>
#include <Shared/Simulation.hh>

namespace gardn {
    class Game {
    public:
        simulation::Simulation simulation;
        float delta;
        Game();
        void Tick(float);
    };
    extern Game game;
    extern renderer::Renderer renderer;
}