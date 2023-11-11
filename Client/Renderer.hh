#pragma once

#include <inttypes.h>

namespace renderer {
    struct RenderFilter {
        uint32_t color;
        float amount;
    };

    class RenderState {
        struct RenderFilter filter;
        float matrix[6];
        float opacity;
    };

    class Renderer {
    public:
        class RenderState state;
        float width;
        float height;
        uint32_t context_id;
        Renderer();
        void SetDimensions(float, float);
        void FillRect(float, float, float, float);
        void ClearRect(float, float, float, float);
        void SetTransform(float, float, float, float, float, float);
    };
}