#include <Shared/Simulation.hh>

#include <iostream>

#include <Server/System/System.hh>

using namespace simulation;

Simulation::Simulation() {
    EntityIdx id = Alloc();
    Arena *arena = Add<Arena>(id);
    arena->radius = 1024;
}

EntityIdx Simulation::Alloc() {
    for (EntityIdx i = 1; i < ENTITY_CAP; ++i) {
        if (EntityTracker[i] == 0) {
            ++EntityHashTracker[i];
            return i;
        }
    }
    return NULL_ENTITY;
}

EntityHash Simulation::GetHash(EntityIdx entity) {
    return entity | (EntityHashTracker[entity] << 16);
}

void Simulation::Tick() {
    system::Velocity(this);
}