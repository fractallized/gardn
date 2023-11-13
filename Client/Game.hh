#pragma once

#include <inttypes.h>

#include <Client/Renderer.hh>
#include <Client/Socket.hh>
#include <Shared/Protocol.hh>
#include <Shared/Simulation.hh>

namespace gardn {
    class Game {
    public:
        simulation::Simulation simulation;
        Socket socket;
        EntityIdx camera_id;
        float delta;
        bool playing;
        Game();
        void Tick(float);
    };
    extern Game game;
    extern renderer::Renderer renderer;
}