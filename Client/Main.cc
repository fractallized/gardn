#include <iostream>

#include <emscripten.h>

#include <Client/Game.hh>

extern "C" {
    void render(float width, float height, float delta) {
        gardn::renderer.width = width;
        gardn::renderer.height = height;
        gardn::game.Tick(delta);
    };
}

static int init() {
    puts("init client");
    EM_ASM({
        Module.canvas = document.createElement("canvas");
        Module.canvas.id = "canvas";
        Module.canvas.oncontextmenu = function() { return false; };
        window.onbeforeunload = function(e) { return "Are you sure?"; };
        document.body.appendChild(Module.canvas);
        Module.ctxs = [Module.canvas.getContext('2d')];
        Module.availableCtxs = new Array(256).fill(0).map(function(_, i) { return i; });
        Module.addCtx = function()
        {
            if (Module.availableCtxs.length)
            {
                const index = Module.availableCtxs.shift();
                if (index == 0)
                    return 0;
                const ocanvas = new OffscreenCanvas(1, 1);
                Module.ctxs[index] = ocanvas.getContext('2d');
                return index;
            }
            throw new Error(
                'Out of Contexts: Can be fixed by allowing more contexts');
            return -1;
        };
        Module.removeCtx = function(index)
        {
            if (index == 0)
                throw new Error('Tried to delete the main context');
            Module.ctxs[index] = null;
            Module.availableCtxs.push(index);
        };
    });
    return 0;
}

volatile int __ = init();
gardn::Game gardn::game;
renderer::Renderer gardn::renderer;

static void loop() {
    EM_ASM({
        window.onkeydown = function(e)
        {
            //_rr_key_event($0, 1, e.which, e.key ? (!e.ctrlKey && !e.metaKey && e.key.length == 1) * e.key.charCodeAt() : 0);
        };
        window.onkeyup = function(e)
        {
            //_rr_key_event($0, 0, e.which, e.key ? (!e.ctrlKey && !e.metaKey && e.key.length == 1) * e.key.charCodeAt() : 0);
        };
        window.addEventListener("mousedown", async function(e)
        {
            const clientX = e.clientX; const clientY = e.clientY; const button = e.button;
            //_rr_mouse_event($0, clientX * devicePixelRatio, clientY * devicePixelRatio, 1, +!!button);
        });
        window.addEventListener("mousemove", async function(e)
        {
            const clientX = e.clientX; const clientY = e.clientY; const button = e.button;
            //_rr_mouse_event($0, clientX * devicePixelRatio, clientY * devicePixelRatio, 2, +!!button);
        });
        window.addEventListener("mouseup", async function(e){
            const clientX = e.clientX; const clientY = e.clientY; const button = e.button;
            //_rr_mouse_event($0, clientX * devicePixelRatio, clientY * devicePixelRatio, 0, +!!button);
        });
        window.addEventListener("touchstart", function(e){
            e.preventDefault();
            e.stopPropagation();
            if (!e.changedTouches.length)
                return;
            const touch = e.changedTouches[0];
            //_rr_mouse_event($0, touch.clientX * devicePixelRatio, touch.clientY * devicePixelRatio, 1, 0);
            for (const t of e.changedTouches);
                //_rr_touch_event($0, t.clientX * devicePixelRatio, t.clientY * devicePixelRatio, 1, t.identifier);
        }, {passive: false});
        window.addEventListener("touchmove", function(e){
            e.preventDefault();
            e.stopPropagation();
            if (!e.changedTouches.length)
                return;
            const touch = e.changedTouches[0];
            //_rr_mouse_event($0, touch.clientX * devicePixelRatio, touch.clientY * devicePixelRatio, 2, 0);
            for (const t of e.changedTouches);
                //_rr_touch_event($0, t.clientX * devicePixelRatio, t.clientY * devicePixelRatio, 1, t.identifier);
        }, {passive: false});
        window.addEventListener("touchend", function(e){
            e.preventDefault();
            e.stopPropagation();
            if (!e.changedTouches.length)
                return;
            const touch = e.changedTouches[0];
            //_rr_mouse_event($0, touch.clientX * devicePixelRatio, touch.clientY * devicePixelRatio, 0, 0);
            for (const t of e.changedTouches);
                //_rr_touch_event($0, t.clientX * devicePixelRatio, t.clientY * devicePixelRatio, 0, t.identifier);
        }, {passive: false});
        window.addEventListener("wheel", async function({deltaY}) {
            //_rr_wheel_event($0, deltaY); 
        });
        document.body.addEventListener("paste", async function(e) {
            const buf = new TextEncoder().encode(e.clipboardData.getData("text/plain"));
            const $a = _malloc(buf.length + 1);
            HEAPU8.set(buf, $a);
            HEAPU8[$a + buf.length] = 0;
            //_rr_paste_event($0, $a);
        });

        function loop(time)
        {
            if (window.start == null)
                window.start = time + 1;
            const delta = Math.min(0.5, (time - window.start) / 1000);
            window.start = time;
            _render(Module.canvas.width = innerWidth * devicePixelRatio, Module.canvas.height = innerHeight * devicePixelRatio, delta);
            requestAnimationFrame(loop);
        };
        requestAnimationFrame(loop);
    });
}

int main() {
    loop();
    return 0;
}