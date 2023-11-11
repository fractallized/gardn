#pragma once

#include <inttypes.h>
#include <stdint.h>

#ifdef CLIENT_SIDE
#define CLIENT_ONLY(...) __VA_ARGS__
#else
#define CLIENT_ONLY(...)
#endif

#ifdef SERVER_SIDE
#define SERVER_ONLY(...) __VA_ARGS__
#else
#define SERVER_ONLY(...)
#endif

namespace utilities {
    void HexDump(uint8_t const *, uint64_t);
    void HexDump(char const *, uint64_t);
    uint64_t GetTime();
    
    class Vector {
    public:
        float x;
        float y;
        Vector();
        Vector(float, float);
        Vector *operator=(Vector *);
        Vector &operator+=(Vector &);
        Vector &operator-=(Vector &);
        Vector &operator*=(float);
        bool operator>(float);
        bool operator<(float);
        Vector FromPolar(float, float);
    };
}