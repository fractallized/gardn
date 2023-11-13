#pragma once

#include <Shared/Entity.hh>
#include <Shared/StaticData.hh>
#include <Shared/Utilities.hh>

namespace simulation {
    class Simulation;
    #define SHG_SIZE (256)
    #define GRID_LENGTH (ARENA_LENGTH + (SHG_SIZE) - 1) / SHG_SIZE
    #define MAX_PER_CELL 512
    class SpatialHash {
        utilities::StaticVector<EntityIdx, MAX_PER_CELL> cells[GRID_LENGTH][GRID_LENGTH];
        Simulation *simulation;
    public:
        SpatialHash(Simulation *sim) : simulation(sim) {}
        void Reset();
        void Insert(EntityIdx);
        void Collide(void (*)(Simulation *, EntityIdx, EntityIdx));
        void Query(float, float, float, float, void *, void (*)(Simulation *, EntityIdx, void *));
    };
};