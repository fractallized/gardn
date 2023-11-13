#include <Shared/Simulation.hh>

#include <iostream>

#include <Shared/Protocol.hh>

using namespace simulation;

Simulation::Simulation() {
}


void Simulation::ReadUpdate(binary::Protocol *coder) {
    while (1) {
        EntityHash enthash = coder->ReadVarUint();
        if (enthash == NULL_ENTITY)
            break;
        EntityIdx entity = (EntityIdx) enthash;
        if ((enthash >> 16) != EntityHashTracker[entity] && HasEntity(entity)) {
            Free(entity);
            Unset(entity);
        } 
        EntityHashTracker[entity] = enthash >> 16;
        EntityTracker[entity] = coder->ReadVarUint();
        #define X(NAME, ID) \
        if (Has<NAME>(entity)) \
            Get<NAME>(entity)->Code<1>(coder);
        PERCOMPONENT
        #undef X
    }
    Tick();
}

void Simulation::Tick() {
    for (EntityIdx i = 1; i < ENTITY_CAP; ++i)
        if (HasEntity(i) && !(EntityTracker[i] & 1))
            Free(i);
    for (EntityIdx i = 1; i < ENTITY_CAP; ++i)
        if (HasEntity(i)) {
            if (!(EntityTracker[i] & 1))
                Unset(i);
            else
                EntityTracker[i] &= ~1;
        }
}