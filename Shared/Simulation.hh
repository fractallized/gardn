#pragma once

#include <Shared/Component/Arena.hh>
#include <Shared/Component/Camera.hh>
#include <Shared/Component/Flower.hh>
#include <Shared/Component/Physical.hh>

#include <Shared/Entity.hh>
#include <Shared/StaticData.hh>
#include <Shared/Utilities.hh>

#ifdef SERVER_SIDE
#include <Server/SpatialHash.hh>
#endif

namespace binary {
    class Protocol;
}

namespace simulation {
    class Simulation {
        uint16_t EntityTracker[ENTITY_CAP] = {0};
        uint16_t EntityHashTracker[ENTITY_CAP] = {0};
    #define X(NAME, ID) \
        NAME NAME##_Components[ENTITY_CAP];
        PERCOMPONENT;
    #undef X
    public:
        SERVER_ONLY(SpatialHash grid;)
        Simulation();
        void Tick();

        SERVER_ONLY(EntityIdx Alloc();)
        SERVER_ONLY(EntityHash GetHash(EntityIdx);)
        SERVER_ONLY(void RequestDelete(EntityIdx);)
        SERVER_ONLY(void WriteUpdate(binary::Protocol *, Camera *);)
        CLIENT_ONLY(void ReadUpdate(binary::Protocol *);)
        SERVER_ONLY(void WriteEntity(EntityIdx, void *);)
        void Free(EntityIdx);
        void Unset(EntityIdx);
        bool HasEntity(EntityIdx entity) { return EntityTracker[entity] != 0; }

        template<typename T>
        T *Add(EntityIdx entity);
        template<typename T>
        bool Has(EntityIdx entity);
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
        bool Has<NAME>(EntityIdx entity) { \
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