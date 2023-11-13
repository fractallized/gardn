#pragma once

#include <inttypes.h>
#include <cstddef>

namespace binary {
    struct Clientbound {
        enum {
            update,
        };
    };

    struct Serverbound {
        enum {
            spawn,
        };
    };
    class Protocol {
        uint8_t *start;
        uint8_t *at;
        uint8_t *end;
    public:
        Protocol(uint8_t *p) {
            start = at = end = p;
        }
        Protocol(uint8_t *p, uint8_t *e) {
            start = at = p;
            end = e;
        }
        uint32_t Size() { return at - start; }
        uint8_t ReadUint8() {
            if (start != end && at == end)
                return 0;
            return *at++;
        }
        uint64_t ReadVarUint() {
            uint8_t byte;
            uint64_t data = 0;
            uint64_t shift = 0;

            do {
                byte = ReadUint8();
                data |= ((byte & 127) << shift);
                shift += 7;
            } while (byte >= 128);

            return data;
        }
        int64_t ReadVarInt() {
            uint64_t vu = ReadVarUint();
            uint64_t a = vu >> 1;
            int64_t res = (a) * (1 - 2 * (vu & 1));
            return res;
        }
        float ReadFloat() {
            return ReadVarInt() * 1.0f / (1 << 10);
        }

        void WriteUint8(uint8_t v) {
            *at++ = v;
        }
        void WriteVarUint(uint64_t v)  {
            while (v > 127)
            {
                WriteUint8((v & 127) | 128);
                v >>= 7;
            }
            WriteUint8(v);
        }
        void WriteVarInt(int64_t v) {
            if (v >= 0)
                WriteVarUint((v << 1));
            else
                WriteVarUint((-v << 1) | 1);
        }
        void WriteFloat(float v) { 
            WriteVarInt(v * (1 << 10)); 
        }

        template<bool Read>
        void Code(uint8_t &v) {
            if (Read) v = ReadUint8();
            else WriteUint8(v);
        }
        template<bool Read>
        void Code(uint32_t &v) {
            if (Read) v = ReadVarUint();
            else WriteVarUint(v);
        }
        template<bool Read>
        void Code(uint64_t &v) {
            if (Read) v = ReadVarUint();
            else WriteVarUint(v);
        }
        template<bool Read>
        void Code(int64_t &v) {
            if (Read) v = ReadVarInt();
            else WriteVarInt(v);
        }
        template<bool Read>
        void Code(float &v) {
            if (Read) v = ReadFloat();
            else WriteFloat(v);
        }
    };
}