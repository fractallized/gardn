#pragma once

#include <Shared/Entity.hh>
#include <Shared/Protocol.hh>
#include <Shared/Utilities.hh>

namespace simulation {
    class Physical {
    public:
        EntityIdx entity_id;
        utilities::Vector position;
        utilities::Vector velocity;
        CLIENT_ONLY(utilities::Vector lerp_position;)
        SERVER_ONLY(utilities::Vector collision_velocity;)
        SERVER_ONLY(utilities::Vector acceleration;)
        float angle;
        float radius;
        SERVER_ONLY(float friction;)
        SERVER_ONLY(float mass;)
        Physical() {}
        void Init(EntityIdx entity) { *this = {}; entity_id = entity; }
        void Free() {}
        template<bool Read>
        void Code(binary::Protocol *bin) {
            bin->Code<Read>(position.x);
            bin->Code<Read>(position.y);
            bin->Code<Read>(angle);
            bin->Code<Read>(radius);
        }
    };
}