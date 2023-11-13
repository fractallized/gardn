#pragma once

#include <Shared/Entity.hh>
#include <Shared/Protocol.hh>
#include <Shared/Utilities.hh>

namespace simulation {
    class Flower {
    public:
        EntityIdx entity_id;
        float eye_angle;
        uint8_t face_flags;
        Flower() {}
        void Init(EntityIdx entity) { *this = {}; entity_id = entity; }
        void Free() {}
        template<bool Read>
        void Code(binary::Protocol *bin) {
            bin->Code<Read>(eye_angle);
            bin->Code<Read>(face_flags);
        }
    };
}