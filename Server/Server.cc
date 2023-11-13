#include <Server/Server.hh>

#include <unistd.h>
#include <iostream>

#include <Shared/Protocol.hh>
#include <Shared/Utilities.hh>

using namespace server;

#define MESSAGE_BUFFER_SIZE (1024 * 1024)

static uint8_t output_buffer[MESSAGE_BUFFER_SIZE] = {0};
static uint8_t *output_packet = output_buffer + LWS_PRE;

static int lws_callback(struct lws *ws, enum lws_callback_reasons reason, void *user, void *packet, size_t size) {
    Server *server = (Server *) lws_context_user(lws_get_context(ws));
    puts("connect");
    switch (reason) {
    case LWS_CALLBACK_ESTABLISHED: {
        for (int i = 0; i < CLIENT_COUNT; ++i) {
            if (server->clients[i].in_use)
                continue;
            Client *client = &server->clients[i];
            client->Init();
            client->socket_handle = ws;
            lws_set_opaque_user_data(ws, client);
            EntityIdx id = server->simulation.Alloc();
            client->camera = server->simulation.Add<simulation::Camera>(id);
            break;
        }
        break;
    }
    case LWS_CALLBACK_SERVER_WRITEABLE: {
        break;
    }
    case LWS_CALLBACK_RECEIVE: {
        break;
    }
    case LWS_CALLBACK_CLOSED: {
        Client *client = (Client *) lws_get_opaque_user_data(ws);
        client->Free();
        break;
    }
    default:
        return 0;
    }

    return 0;
}


Server::Server() {
    puts("starting...");
    {
        struct lws_context_creation_info info = {0};

        info.protocols = (struct lws_protocols[]){{"g", lws_callback, sizeof(uint8_t), MESSAGE_BUFFER_SIZE, 0, nullptr, 0}, {0}};
        info.port = 1234;
        info.user = this;
        info.pt_serv_buf_size = MESSAGE_BUFFER_SIZE;

        server = lws_create_context(&info);
    }

    while (1)
    {
        uint64_t start = utilities::GetTime();
        lws_service(server, -1);
        Tick();
        uint64_t end = utilities::GetTime();
        uint64_t dur = end - start;
        if (end - start < 25000)
            usleep(25000 - end + start);
    }
}

void Server::Tick() {
    simulation.Tick();
    for (uint32_t i = 0; i < CLIENT_COUNT; ++i)
        if (clients[i].in_use)
            clients[i].Tick();
}

void Client::Tick() {
    if (camera == nullptr)
        return;
    binary::Protocol writer(output_packet);
    writer.WriteUint8(0);
    writer.WriteVarUint(camera->entity_id);
    gardn.simulation.WriteUpdate(&writer, camera);
    lws_write(socket_handle, output_packet, writer.Size(), LWS_WRITE_BINARY);
}

void Client::Free() {
    in_use = 0; 
    socket_handle = nullptr; 
    if (camera != nullptr) 
        gardn.simulation.RequestDelete(camera->entity_id);
}