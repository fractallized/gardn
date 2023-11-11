#include <Shared/Simulation.hh>

#include <iostream>

using namespace simulation;

void Simulation::Free(EntityIdx entity) {
    #define X(NAME, ID) \
        if (Has<NAME>(entity)) \
            Get<NAME>(entity)->Free();
    PERCOMPONENT
    #undef X
}

void Simulation::Unset(EntityIdx entity) {
    EntityTracker[entity] = 0;
}