#pragma once

#include <Shared/Entity.hh>
#include <Shared/Protocol.hh>
#include <Shared/Utilities.hh>

namespace simulation {
    class Camera {
    public:
        EntityIdx entity_id;
        utilities::Vector position;
        float fov;
        EntityHash player;
        Camera() {}
        void Init(EntityIdx entity) { *this = {}; entity_id = entity; fov = 1; }
        void Free() {}
        template<bool Read>
        void Code(binary::Protocol *bin) {
            bin->Code<Read>(position.x);
            bin->Code<Read>(position.y);
            bin->Code<Read>(fov);
            bin->Code<Read>(player);
        }
    };
}