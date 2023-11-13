#include <Server/System/System.hh>

#include <iostream>

using namespace simulation;

static void ForEach(Simulation *simulation, EntityIdx entity, void *captures) {
    simulation->grid.Insert(entity);
}

void system::Physics(Simulation *simulation) {
    simulation->grid.Reset();
    simulation->ForEach<Physical>(NULL, ForEach);
}