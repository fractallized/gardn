#pragma once

#include <inttypes.h>
#include <libwebsockets.h>

#include <Shared/Simulation.hh>
#include <Shared/Utilities.hh>

namespace server {
    #define CLIENT_COUNT (64)

    class Client {
    public:
        simulation::Camera *camera;
        struct lws *socket_handle;
        utilities::Vector player_acceleration;
        bool in_use;
        bool verified;
        Client() : camera(nullptr), socket_handle(nullptr) {};
        void Init() { *this = {}; in_use = 1; };
        void Free();
        void Tick();
    };

    class Server {
    public:
        simulation::Simulation simulation;
        struct lws_context *server;
        Client clients[CLIENT_COUNT];
        Server();
        void Tick();
    };
    extern Server gardn;
}