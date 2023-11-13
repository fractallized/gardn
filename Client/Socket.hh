#pragma once

#include <inttypes.h>

namespace gardn {
    extern uint8_t socket_buffer[1024 * 1024];
    class Socket {
        bool ready;
        bool pending;
    public:
        Socket() : pending(false), ready(false) {}
        void Connect(char *);
        void Disconnect();
        void Send(uint8_t *, uint32_t);
    };
}