#pragma once

#include <inttypes.h>

namespace renderer {
    struct RenderFilter {
        uint32_t color;
        float amount;
    };

    class RenderState {
    public:
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

        void SetFill(uint32_t);
        void SetStroke(uint32_t);
        void SetLineWidth(float);
        void SetTextSize(float);
        void SetLineCap(int);
        void SetLineJoin(int);
        void SetTextAlign(int);
        void SetTextBaseline(int);
        
        void SetTransform(float, float, float, float, float, float);
        void Translate(float, float);
        void Rotate(float);
        void Scale2(float, float);
        void Scale(float);
        void ResetTransform();

        void BeginPath();
        void MoveTo(float, float);
        void LineTo(float, float);
        void QuadraticCurveTo(float, float, float, float);
        void BezierCurveTo(float, float, float, float, float, float);
        void PartialArc(float, float, float, float, float, bool);
        void Arc(float, float, float);
        void Fill();
        void Stroke();
        void FillRect(float, float, float, float);
        void ClearRect(float, float, float, float);
    };
}