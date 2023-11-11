#pragma once

#include <Shared/Component/Arena.hh>
#include <Shared/Component/Camera.hh>
#include <Shared/Component/Physical.hh>

#include <Shared/Entity.hh>
#include <Shared/Utilities.hh>

namespace simulation {
    class Simulation {
        uint16_t EntityTracker[ENTITY_CAP] = {0};
        SERVER_ONLY(uint16_t EntityHashTracker[ENTITY_CAP] = {0};)
    #define X(NAME, ID) \
        NAME NAME##_Components[ENTITY_CAP];
        PERCOMPONENT;
    #undef X
    public:
        Simulation();
        void Tick();

        SERVER_ONLY(EntityIdx Alloc();)
        SERVER_ONLY(EntityHash GetHash(EntityIdx);)
        void Free(EntityIdx);
        void Unset(EntityIdx);

        template<typename T>
        T *Add(EntityIdx entity);
        template<typename T>
        int Has(EntityIdx entity);
        template<typename T>
        T *Get(EntityIdx entity);
        template<typename T>
        void ForEach(void *capture, void (*cb)(Simulation *, EntityIdx, void *));

        #define X(NAME, ID) \
        template <> \
        NAME *Add<NAME>(EntityIdx entity) { \
            NAME##_Components[entity].Init(entity); \
            EntityTracker[entity] |= (1 << ID); \
            return &NAME##_Components[entity]; \
        } \
        template <> \
        int Has<NAME>(EntityIdx entity) { \
            return (EntityTracker[entity] >> ID) & 1; \
        } \
        template <> \
        NAME *Get<NAME>(EntityIdx entity) { \
            return &NAME##_Components[entity]; \
        } \
        template <> \
        void ForEach<NAME>(void *capture, void (*cb)(Simulation *, EntityIdx, void *)) { \
            for (EntityIdx i = 1; i < ENTITY_CAP; ++i) \
                if (Has<NAME>(i)) \
                    cb(this, i, capture); \
        }
        PERCOMPONENT
        #undef X
    }; 
}