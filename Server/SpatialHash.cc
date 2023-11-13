#include <Server/SpatialHash.hh>

#include <iostream>

#include <Shared/Simulation.hh>

using namespace simulation;

void SpatialHash::Reset() {
    for (uint32_t y = 0; y < GRID_LENGTH; ++y)
        for (uint32_t x = 0; x < GRID_LENGTH; ++x)
            cells[x][y].Clear();
}

void SpatialHash::Insert(EntityIdx entity) {
    Physical *physical = simulation->Get<Physical>(entity);
    uint32_t sx = utilities::FClamp(physical->position.x, 0, ARENA_LENGTH - SHG_SIZE) / SHG_SIZE;
    uint32_t sy = utilities::FClamp(physical->position.y, 0, ARENA_LENGTH - SHG_SIZE) / SHG_SIZE;
    cells[sx][sy].Add(entity);
}

void SpatialHash::Collide(void (*cb)(Simulation *, EntityIdx, EntityIdx)) {

}

void SpatialHash::Query(float vx, float vy, float vw, float vh, void *captures, void (*cb)(Simulation *, EntityIdx, void *)) {
    uint32_t sx = utilities::FClamp(vx - vw - SHG_SIZE, 0, ARENA_LENGTH - SHG_SIZE) / SHG_SIZE;
    uint32_t sy = utilities::FClamp(vy - vh - SHG_SIZE, 0, ARENA_LENGTH - SHG_SIZE) / SHG_SIZE;
    uint32_t ex = utilities::FClamp(vx + vw + SHG_SIZE, 0, ARENA_LENGTH - SHG_SIZE) / SHG_SIZE;
    uint32_t ey = utilities::FClamp(vy + vh + SHG_SIZE, 0, ARENA_LENGTH - SHG_SIZE) / SHG_SIZE;
    for (uint32_t y = sy; y <= ey; ++y)
        for (uint32_t x = sx; x <= ex; ++x)
            for (uint32_t i = 0; i < cells[x][y].Size(); ++i)
                cb(simulation, cells[x][y][i], captures);
}