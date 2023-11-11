#pragma once

#include <Shared/Entity.hh>
#include <Shared/Protocol.hh>

namespace simulation {
    class Arena {
    public:
        EntityIdx entity_id;
        float radius;
        Arena() {}
        void Init(EntityIdx entity) { *this = {}; entity_id = entity; }
        void Free() {}
        template<bool Read>
        void Code(binary::Protocol *bin) {
            bin->Code<Read>(radius);
        }
    };
}