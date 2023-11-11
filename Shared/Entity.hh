#pragma once

#include <inttypes.h>

#define ENTITY_CAP (1024)
#define NULL_ENTITY (0)

typedef uint16_t EntityIdx;
typedef uint32_t EntityHash;

#define PERCOMPONENT \
    X(Physical, 1)   \
    X(Arena, 2)      \
    X(Camera, 3)