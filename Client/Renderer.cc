#include <Renderer.hh>

#include <cmath>
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

void Renderer::SetFill(uint32_t c) {
    EM_ASM({
        Module.ctxs[$0].fillStyle = "rgba("+$1+","+$2+","+$3+","+$4+")";
    }, context_id, (uint8_t) (c >> 16), (uint8_t) (c >> 8), (uint8_t) c, (uint8_t) (c >> 24) / 255.0f);
}

void Renderer::SetStroke(uint32_t c) {
    EM_ASM({
        Module.ctxs[$0].strokeStyle = "rgba("+$1+","+$2+","+$3+","+$4+")";
    }, context_id, (uint8_t) (c >> 16), (uint8_t) (c >> 8), (uint8_t) c, (uint8_t) (c >> 24) / 255.0f);
}

void Renderer::SetLineWidth(float c) {
    EM_ASM({
        Module.ctxs[$0].lineWidth = $1;
    }, context_id, c);
}

void Renderer::SetTextSize(float c) {
    EM_ASM({
        Module.ctxs[$0].font = $1 + "px Ubuntu";
    }, context_id, c);
}

void Renderer::SetLineJoin(int c) {
    EM_ASM({
        Module.ctxs[$0].lineJoin = $1 === -1 ? "miter" : $1 === 0 ? "round" : "bevel";
    }, context_id, c);
}

void Renderer::SetLineCap(int c) {
    EM_ASM({
        Module.ctxs[$0].lineCap = $1 === -1 ? "butt" : $1 === 0 ? "round" : "square";
    }, context_id, c);
}

void Renderer::SetTextAlign(int c) {
    EM_ASM({
        Module.ctxs[$0].textAlign = $1 === -1 ? "left" : $1 === 0 ? "center" : "right";
    }, context_id, c);
}

void Renderer::SetTextBaseline(int c) {
    EM_ASM({
        Module.ctxs[$0].textAlign = $1 === -1 ? "top" : $1 === 0 ? "middle" : "bottom";
    }, context_id, c);
}

static void UpdateTransform(Renderer *r) {
    EM_ASM({
         Module.ctxs[$0].setTransform($1, $2, $4, $5, $3, $6);
    }, r->context_id, r->state.matrix[0], r->state.matrix[1], r->state.matrix[2], 
    r->state.matrix[3], r->state.matrix[4], r->state.matrix[5]);
}

void Renderer::SetTransform(float a, float b, float c, float d, float e, float f) {
    state.matrix[0] = a;
    state.matrix[1] = b;
    state.matrix[2] = c;
    state.matrix[3] = d;
    state.matrix[4] = e;
    state.matrix[5] = f;
    UpdateTransform(this);
}

void Renderer::Translate(float x, float y) {
    state.matrix[2] += x * state.matrix[0] + y * state.matrix[3];
    state.matrix[5] += x * state.matrix[1] + y * state.matrix[4];
    UpdateTransform(this);
}

void Renderer::Rotate(float a) {
    float cos_a = cosf(a);
    float sin_a = sinf(a);
    float original0 = state.matrix[0];
    float original1 = state.matrix[1];
    float original3 = state.matrix[3];
    float original4 = state.matrix[4];
    state.matrix[0] = original0 * cos_a + original1 * -sin_a;
    state.matrix[1] = original0 * sin_a + original1 * cos_a;
    state.matrix[3] = original3 * cos_a + original4 * -sin_a;
    state.matrix[4] = original3 * sin_a + original4 * cos_a;
    UpdateTransform(this);
}

void Renderer::Scale2(float x, float y) {
    state.matrix[0] *= x;
    state.matrix[1] *= x;
    state.matrix[3] *= y;
    state.matrix[4] *= y;
    UpdateTransform(this);
}

void Renderer::Scale(float x) {
    Scale2(x, x);
    UpdateTransform(this);
}

void Renderer::ResetTransform() {
    SetTransform(1,0,0,0,1,0);
}

void Renderer::BeginPath() {
    EM_ASM({
        Module.ctxs[$0].beginPath();
    }, context_id);
}

void Renderer::MoveTo(float x, float y) {
    EM_ASM({
        Module.ctxs[$0].moveTo($1, $2);
    }, context_id, x, y);
}

void Renderer::LineTo(float x, float y) {
    EM_ASM({
        Module.ctxs[$0].lineTo($1, $2);
    }, context_id, x, y);
}

void Renderer::QuadraticCurveTo(float x1, float y1, float x, float y) {
    EM_ASM({
        Module.ctxs[$0].quadraticCurveTo($1, $2, $3, $4);
    }, context_id, x1, y1, x, y);
}

void Renderer::BezierCurveTo(float x1, float y1, float x2, float y2, float x, float y) {
    EM_ASM({
        Module.ctxs[$0].bezierCurveTo($1, $2, $3, $4, $5, $6);
    }, context_id, x1, y1, x2, y2, x, y);
}

void Renderer::PartialArc(float x, float y, float r, float sa, float ea, bool cw) {
    EM_ASM({
        Module.ctxs[$0].arc($1, $2, $3, $4, $5, !!$6);
    }, context_id, x, y, r, sa, ea, cw);
}

void Renderer::Arc(float x, float y, float r) {
    PartialArc(x, y, r, 0, 2 * M_PI, 0);
}

void Renderer::Fill() {
    EM_ASM({
        Module.ctxs[$0].fill();
    }, context_id);
}

void Renderer::Stroke() {
    EM_ASM({
        Module.ctxs[$0].stroke();
    }, context_id);
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
