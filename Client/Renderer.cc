#include <Renderer.hh>

#include <emscripten.h>

using namespace renderer;

Renderer::Renderer() {
    context_id = EM_ASM_INT({
        return Module.addCtx();
    });
}

void Renderer::SetDimensions(float w, float h) {
    EM_ASM({
        const canvas = Module.ctxs[$0].canvas;
        canvas.width = $1;
        canvas.height = $2;
    }, context_id, w, h);
}

void Renderer::ClearRect(float x, float y, float w, float h) {
    EM_ASM({
        Module.ctxs[$0].clearRect($1, $2, $3, $4);
    }, context_id, x, y, w, h);
}

void Renderer::FillRect(float x, float y, float w, float h) {
    EM_ASM({
        Module.ctxs[$0].fillRect($1, $2, $3, $4);
    }, context_id, x, y, w, h);
}

void Renderer::SetTransform(float a, float b, float c, float d, float e, float f) {
    EM_ASM({
         Module.ctxs[$0].setTransform($1, $2, $3, $4, $5, $6);
    }, context_id, a, b, c, d, e, f);
}