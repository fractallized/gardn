#include <Server/System/System.hh>

#include <iostream>

using namespace simulation;

static void ForEach(Simulation *simulation, EntityIdx entity, void *captures) {
    Physical *physical = simulation->Get<Physical>(entity);
    physical->velocity *= physical->friction;
    physical->velocity += physical->acceleration;
    physical->position += physical->velocity;
}

void system::Velocity(Simulation *simulation) {
    simulation->ForEach<Physical>(NULL, ForEach);
}