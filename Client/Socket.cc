#include <Client/Socket.hh>

#include <iostream>
#include <emscripten.h>

#include <Client/Game.hh>
#include <Shared/Protocol.hh>

using namespace gardn;

uint8_t gardn::socket_buffer[1024 * 1024] = {0};

extern "C" {
    void socket_event(uint8_t type, uint32_t length) {
        switch (type) {
            case 0:
                break;
            case 1: {
                binary::Protocol decoder(socket_buffer);
                switch(decoder.ReadUint8()) {
                    case binary::Clientbound::update: {
                        game.camera_id = decoder.ReadVarUint();
                        game.simulation.ReadUpdate(&decoder);
                        break;
                    }
                }
                break;
            }
            case 2:
                break;
        }
    }
}

void Socket::Connect(char *address) {
    EM_ASM({
        let socket = Module.socket = new WebSocket(UTF8ToString($0));
        socket.binaryType = "arraybuffer";
        socket.onopen = function() {
            _socket_event(0, 0);
        };
        socket.onmessage = function(event)
        {
            const b = new Uint8Array(event.data);
            HEAPU8.set(b, $1);
            _socket_event(1, b.length);
        };
        socket.onclose = function(a) {
            _socket_event(2, a.code);
        };
    }, address, socket_buffer);
}

void Socket::Send(uint8_t *ptr, uint32_t len) {
    EM_ASM({
        Module.socket.send(HEAPU8.subarray($0, $0 + $1));
    }, ptr, len);
}