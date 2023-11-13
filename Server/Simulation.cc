#include <Shared/Simulation.hh>

#include <iostream>

#include <Server/System/System.hh>
#include <Shared/Protocol.hh>

using namespace simulation;

Simulation::Simulation() : grid(this) {
    EntityIdx id = Alloc();
    Arena *arena = Add<Arena>(id);
    arena->radius = ARENA_LENGTH;
    id = Alloc();
    Physical *physical = Add<Physical>(id);
    physical->velocity.x = 1.5;
    physical->friction = 1;
}

EntityIdx Simulation::Alloc() {
    for (EntityIdx i = 1; i < ENTITY_CAP; ++i) {
        if (EntityTracker[i] == 0) {
            ++EntityHashTracker[i];
            EntityTracker[i] |= 1;
            return i;
        }
    }
    return NULL_ENTITY;
}

EntityHash Simulation::GetHash(EntityIdx entity) {
    return entity | (EntityHashTracker[entity] << 16);
}

void Simulation::RequestDelete(EntityIdx entity) {
    if (EntityTracker[entity] == 0)
        return;
    EntityTracker[entity] &= ~1;
}

void Simulation::Tick() {
    system::Physics(this);
    system::Velocity(this);
    for (EntityIdx i = 1; i < ENTITY_CAP; ++i)
        if (HasEntity(i) && !(EntityTracker[i] & 1))
            Free(i);
    for (EntityIdx i = 1; i < ENTITY_CAP; ++i)
        if (HasEntity(i) && !(EntityTracker[i] & 1))
            Unset(i);
}

static void wrapper_write_entity(Simulation *simulation, EntityIdx entity, void *captures) {
    Physical *physical = simulation->Get<Physical>(entity);
    simulation->WriteEntity(entity, captures);
}

void Simulation::WriteEntity(EntityIdx entity, void *_coder) {
    binary::Protocol *coder = (binary::Protocol *) _coder;
    coder->WriteVarUint(GetHash(entity));
    coder->WriteVarUint(EntityTracker[entity]);
    #define X(NAME, ID) \
        if (Has<NAME>(entity)) \
            Get<NAME>(entity)->Code<0>(coder);
    PERCOMPONENT
    #undef X
}

void Simulation::WriteUpdate(binary::Protocol *coder, Camera *camera) {
    WriteEntity(camera->entity_id, coder);
    grid.Query(camera->position.x, camera->position.y, 960 / camera->fov, 540 / camera->fov, coder, wrapper_write_entity);
    coder->WriteVarUint(NULL_ENTITY);
}