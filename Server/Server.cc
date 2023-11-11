#include <Server/Server.hh>

#include <unistd.h>

#include <Shared/Utilities.hh>

using namespace server;

#define MESSAGE_BUFFER_SIZE (1024 * 1024)

static int lws_callback(struct lws *ws, enum lws_callback_reasons reason,
                        void *user, void *packet, size_t size)
{
    switch (reason)
    {
    case LWS_CALLBACK_ESTABLISHED:
    case LWS_CALLBACK_SERVER_WRITEABLE:
    case LWS_CALLBACK_RECEIVE:
    case LWS_CALLBACK_CLOSED:
        break;
    default:
        return 0;
    }
    // assert(pthread_mutex_lock(&mutex) == 0);

    //struct rr_server *this =
        //(struct rr_server *)lws_context_user(lws_get_context(ws));
    //int close = handle_lws_event(this, ws, reason, packet, size);
    //if (close)
        //return close;
    // assert(pthread_mutex_unlock(&mutex) == 0);
    return 0;
}


Server::Server() {
    puts("starting...");
    {
        struct lws_context_creation_info info = {0};

        info.protocols =
            (struct lws_protocols[]){{"g", lws_callback, sizeof(uint8_t),
                                      MESSAGE_BUFFER_SIZE, 0, NULL, 0},
                                     {0}};

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
            usleep(25000 - end + start); //fix
    }
}

void Server::Tick() {
    simulation.Tick();   
}