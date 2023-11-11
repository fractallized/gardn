#pragma once

#include <inttypes.h>
#include <libwebsockets.h>

#include <Shared/Simulation.hh>

namespace server {
    class Server {
    public:
        simulation::Simulation simulation;
        struct lws_context *server;
        Server();
        void Tick();
    };
    extern Server gardn;
}